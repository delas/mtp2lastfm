#include "loaderthread.h"
#include <iostream>

LoaderThread::LoaderThread(const QString& db_path,
						   const QString& old_xml_file_path,
						   QObject *parent)
		: QThread(parent)
{
	m_db_path = db_path;
	m_old_xml_file_path = old_xml_file_path;

	m_configurationloading = new ConfigurationLoading(this);
	m_mainwindow = new MainWindow(this);
	m_configurationloading->show();
}


void LoaderThread::run()
{
	/**************************************************************************/
	/* Database */
	emit updateProgress(tr("Checking database presence..."), 5);
	if(SQLiteORM::initDB(m_db_path))
	{
		qDebug("LoaderThread : Database initialized");

		emit updateProgress(tr("Database connected!"), 10);
		if (SQLiteORM::getNumberOfDBTables() == 0)
		{
			qDebug("LoaderThread : Database empty");

			emit updateProgress(tr("Database empty, creating tables..."), 20);
			SQLiteORM::execSQL(SQL_CREATE_TABLES);
			emit updateProgress(tr("Inserting base rows..."), 27);
			SQLiteORM::execSQL(SQL_BASE_INSERT);

			/* Checking XML early version */
			emit updateProgress(tr("Checking XML file presence..."), 34);
			QFile xml_old(m_old_xml_file_path);
			if (xml_old.exists())
			{
				qDebug("LoaderThread : Found an XML file to import");

				emit updateProgress(tr("File exists, importing..."), 35);
				if (xml_old.open(QIODevice::ReadOnly))
				{
					QDomDocument doc;
					if (doc.setContent(xml_old.readAll()))
					{
						emit updateProgress(tr("Loading user info..."),
											40);
						QString lastfm_username = doc
												  .elementsByTagName("username")
												  .item(0).toElement().text();
						DBConfig::get("LASTFM_USERNAME").value(lastfm_username);
						qDebug("LoaderThread : LASTFM_USERNAME = %s", lastfm_username.toStdString().c_str());

						QString lastfm_pass = doc
											  .elementsByTagName("passwordMd5Hash")
											  .item(0).toElement().text();
						DBConfig::get("LASTFM_PASSHASH").value(lastfm_pass);
						qDebug("LoaderThread : LASTFM_PASSHASH = %s", lastfm_pass.toStdString().c_str());

						emit updateProgress(tr("Loading scrobbled tracks..."),
											45);
						QDomNodeList list = doc.elementsByTagName("track");
						qDebug("LoaderThread : Document to import: %d", list.size());

						for (int i = 0; i < list.size(); i++)
						{
							QString title =
									list.at(i).firstChildElement("title").text();
							QString artist =
									list.at(i).firstChildElement("artist").text();
							QString album =
									list.at(i).firstChildElement("album").text();
							int album_position =
									list.at(i).firstChildElement("albumPosition").text().toInt();
							int length =
									list.at(i).firstChildElement("length").text().toInt();
							int play_count =
									list.at(i).firstChildElement("playCount").text().toInt();
							qDebug("LoaderThread : Importing %d \t %s",
								   i, title.toStdString().c_str());

							Track t = Track::get(artist, title);
							t.setAlbum(album);
							t.setAlbumPosition(album_position);
							t.setLength(length);
							t.setScrobbleDone(play_count);
							t.save();
						}
					}
				}
				else
				{
					emit updateProgress(tr("Can't open file!"), 40);
				}
			}
		}
	}
	else
	{
		emit updateProgress(tr("Database connection error..."), 100);
		return;
	}

	/* Now we are to 50% loaded */
	emit updateProgress(tr("Database reading complete!"), 50);

	/**************************************************************************/
	/* Checking previous versions */
	// No previous version! :)

	emit updateProgress(tr("Application loaded!"), 100);



	/* Ok, loading complete, let's begin real stuff */
	emit startMain();
}
