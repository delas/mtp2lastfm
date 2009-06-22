#ifndef SCROBBLER_H
#define SCROBBLER_H

#include <QThread>
#include <QtNetwork>
#include "../view/scrobblerprogress.h"
#include "../model/track.h"
#include "../model/dbconfig.h"
#include "../model/md5.h"
#include "../config.h"

/**
 *
 * @author Andrea Burattin
 */
class Scrobbler : public QThread
{
	Q_OBJECT

	public:
	Scrobbler(QObject *parent = 0);
	~Scrobbler();

	protected:
	/**
	 * Thread body
	 */
	void run();

	/**
	 * This method starts the submission session, with the default Last.fm
	 * handshake protocol
	 *
	 * @param uri the url with the scrobbling instructions
	 * @see lastfm_responses
	 * @see http://www.last.fm/api/submissions#handshake
	 * @return a handshake response value
	 */
	int lastfm_handshake(QString& uri);

	/**
	 * This method submits the parameter track. It supposes that the handshake
	 * has been already done.
	 *
	 * @see lastfm_responses
	 * @param t the track to scrobble
	 * @return a scrobble response value
	 */
	int lastfm_scrobble_track(Track& t);


	signals:
	/**
	 * This signal is emitted to send update informations
	 *
	 * @param action a string to describe the in progress action
	 * @param steps new, percentual, of completed job
	 */
	void updateProgress(const QString& action, int steps);

	/**
	 * This signal is emitted when there is an error
	 *
	 * @param error the error description
	 */
	void errorCatched(const QString& error);


	private slots:
	/**
	 * Slot to capture the end of the HTTP transaction
	 *
	 * @param error is some error occurs
	 */
	void httpDone(bool error);


	private:
	ScrobblerProgress* m_scrobblerprogress;
	QHttp* m_http;
	QBuffer* m_buffer;

	QString m_session_id;
	QString m_session_url;
	QString m_password;
	QString m_username;
	QString m_uri;
	QString m_lasterror;
	int m_to_scrobble_count, m_scrobble_progress, m_timestamp_scrobble;

	QWaitCondition httpProcessed;
	QMutex mutex;
};

#endif // SCROBBLER_H
