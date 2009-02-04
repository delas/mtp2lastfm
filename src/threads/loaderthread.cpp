#include "loaderthread.h"

LoaderThread::LoaderThread(const QString& db_path,
						   const QString& old_xml_file_path,
						   QObject *parent)
		: QThread(parent)
{
	m_db_path = db_path;
	m_old_xml_file_path = old_xml_file_path;

	m_configurationloading = new ConfigurationLoading(this);
	m_configurationloading->show();
}


void LoaderThread::run()
{
	/**************************************************************************/
	/* Database */
	emit updateProgress(tr("Checking database presence..."), 5);
	if(SQLiteORM::initDB(m_db_path))
	{
		emit updateProgress(tr("Database connected!"), 10);
		if (SQLiteORM::getNumberOfDBTables() == 0)
		{
			emit updateProgress(tr("Database empty, creating tables..."), 20);
			SQLiteORM::execSQL(SQL_CREATE_TABLES);
			emit updateProgress(tr("Inserting base rows..."), 27);
			SQLiteORM::execSQL(SQL_BASE_INSERT);

			/* Checking XML early version */
			emit updateProgress(tr("Checking XML file presence..."), 34);
			QFile xml_old(m_old_xml_file_path);
			if (xml_old.exists())
			{
				emit updateProgress(tr("File exists, importing..."), 35);
				if (xml_old.open(QIODevice::ReadOnly))
				{
					QDomDocument doc;
					if (doc.setContent(xml_old.readAll()))
					{
						emit updateProgress(tr("Loading user info..."),
											40);
						// ...
						emit updateProgress(tr("Loading scrobbled tracks..."),
											45);
						// ...
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
}
