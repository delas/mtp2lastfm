#include "scrobbler.h"

Scrobbler::Scrobbler(QObject *parent)
		: QThread(parent)
{
	m_http = new QHttp(this);
	m_buffer = new QBuffer(this);
	m_buffer->open(QIODevice::ReadWrite);

	connect(m_http, SIGNAL(done(bool)),
			this, SLOT(httpDone(bool)));

	m_password = DBConfig::get("LASTFM_PASSHASH").value();
	m_username = DBConfig::get("LASTFM_USERNAME").value();

	m_scrobblerprogress = new ScrobblerProgress(this);
	m_scrobblerprogress->show();

	qDebug("Scrobbler : New thread created");
}


Scrobbler::~Scrobbler()
{
	if (m_http)
	{
		m_http->close();
		delete m_http;
	}
}


void Scrobbler::run()
{
	qDebug("Scrobbler : Thread started");
	emit updateProgress(tr("Scrobbler synchronization..."), 0);
	int out = lastfm_handshake();
	qsrand((unsigned)time(0)); /* randomizer */

	/* check handshake response */
	if (out == lastfm_responses::OK)
	{
		QList<Track> to_scrobble = Track::getToScrobble();
		int curr_track_position = -1;
		m_timestamp_scrobble = QDateTime::currentDateTime().toTime_t()-((m_to_scrobble_count-m_scrobble_progress)*AVG_SONG_LENGTH);
		m_to_scrobble_count = Track::getToScrobbleCount(to_scrobble);
		m_scrobble_progress = 1;

		emit updateProgress(tr("Scrobbling starting..."), 1);
		while (!to_scrobble.empty())
		{
			/* takes every track in random order */
			curr_track_position = qrand() % to_scrobble.size();

			Track t = to_scrobble.takeAt(curr_track_position);
			out = lastfm_scrobble_track(t);
		}
		emit updateProgress(tr("Scrobbling complete!"), 100);
	}
	else
	{
		QString error;
		if (out == lastfm_responses::BADAUTH)
		{
			error = tr("ERROR: Username or password wrong!");
		}
		else if (out == lastfm_responses::BANNED)
		{
			error = tr("ERROR: This user has been banned from Last.fm!");
		}
		else if (out == lastfm_responses::FAILED)
		{
			error = m_lasterror;
		}
		emit errorCatched(error);
	}
	qDebug("Scrobbler : Thread finished");
}


int Scrobbler::lastfm_handshake()
{
	/* get the timestamp */
	QString timestamp_ = QString("%1").arg(QDateTime::currentDateTime().toTime_t());

	/* generate the token */
	QString to_token = m_password.append(timestamp_);
	char* chr_token = MD5String((char*)to_token.toStdString().c_str());
	QString token(chr_token);

	/* generate the get parameters */
	QString url_param = QString(LASTFM_HANDSHAKE_PARAMS)
						.arg(CLIENT_ID)
						.arg(CLIENT_VERSION)
						.arg(m_username)
						.arg(timestamp_)
						.arg(token);

	/* start the handshake process */
	QUrl url(LASTFM_HANDSHAKE);
	QByteArray path = url.path().toAscii();
	path.append(url_param);
	m_buffer = new QBuffer();

	m_http->setHost(url.host());
	m_http->get(path, m_buffer);

	qDebug("Scrobbler : Zzz...");
	mutex.lock();
	httpProcessed.wait(&mutex);
	mutex.unlock();

	QString response(m_buffer->data());
	/* buffer cleaning */
	m_buffer->close(); delete m_buffer;
	QStringList responses = response.split("\n");

	qDebug(response.toStdString().c_str());

	if (responses[0] == "OK")
	{
		m_session_id = responses[1];
		m_session_url = responses[3];
		return lastfm_responses::OK;
	}
	else if (responses[0] == "BANNED")
	{
		return lastfm_responses::BANNED;
	}
	else if (responses[0] == "BADAUTH")
	{
		return lastfm_responses::BADAUTH;
	}
	else if (responses[0] == "BADTIME")
	{
		return lastfm_responses::BADTIME;
	}
	else if (responses[0].contains("FAILED"))
	{
		m_lasterror = responses[0];
		return lastfm_responses::FAILED;
	}
	return lastfm_responses::FAILED;
}


int Scrobbler::lastfm_scrobble_track(Track& t)
{
	int scrobble_times = 0;
	while(t.getScrobbleLeft() > 0)
	{
		/* generate the post parameters */
		QString post_parameters;
		post_parameters.append("s=").append(m_session_id);
		post_parameters.append("&a[0]=").append(QString(QUrl::toPercentEncoding(t.getArtist())));
		post_parameters.append("&t[0]=").append(QString(QUrl::toPercentEncoding(t.getTitle())));
		post_parameters.append("&i[0]=").append(QString("%1").arg(m_timestamp_scrobble));
		post_parameters.append("&o[0]=").append("P");
		post_parameters.append("&r[0]=").append("");
		post_parameters.append("&l[0]=").append(QString("%1").arg(t.getLength()));
		post_parameters.append("&b[0]=").append(QString(QUrl::toPercentEncoding(t.getAlbum())));
		post_parameters.append("&n[0]=").append(QString("%1").arg(t.getAlbumPosition()));
		post_parameters.append("&m[0]=").append("");

		/* progress signal */
		int percent = m_scrobble_progress*100/m_to_scrobble_count;
		QString str_progress = tr("Scrobbling track %1 of %2...")
							   .arg(m_scrobble_progress)
							   .arg(m_to_scrobble_count);
		emit updateProgress(str_progress, percent);

		/* start the scrobble process */
		QUrl url(m_session_url);

		QHttpRequestHeader header("POST", url.path());
		header.setValue("Content-Type", "application/x-www-form-urlencoded");
		header.setValue("Host", url.host());

		m_buffer = new QBuffer();
		m_http->setHost(url.host(), url.port(80));
		m_http->request(header, post_parameters.toAscii(), m_buffer);

		qDebug("Scrobbler : Zzz...");
		mutex.lock();
		httpProcessed.wait(&mutex);
		mutex.unlock();

		QString response(m_buffer->data());
		/* buffer cleaning */
		m_buffer->close(); delete m_buffer;
		QStringList responses = response.split("\n");

		qDebug(response.toStdString().c_str());

		if (responses[0] == "OK")
		{
			t.scrobbled(1);
			t.save();
			scrobble_times++;
			m_scrobble_progress++;
			m_timestamp_scrobble += AVG_SONG_LENGTH;
		}
		else if (responses[0] == "BADSESSION")
		{
			lastfm_handshake();
		}
		else
		{
			m_lasterror = responses[0];
			return lastfm_responses::FAILED;
		}
	}
	return lastfm_responses::OK;
}


void Scrobbler::httpDone(bool errors)
{
	if (errors)
	{
		qDebug("Scrobbler : Connection error");
	}
	else
	{
		qDebug("Scrobbler : Connection established");
	}

	qDebug("Scrobbler : DRIIIIIIL, time to wake up");
	httpProcessed.wakeAll();
}
