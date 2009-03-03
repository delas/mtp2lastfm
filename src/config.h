#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

/** The client identifier */
const QString CLIENT_ID = "mtp";
//const QString CLIENT_ID = "tst";

/** The current client version */
const QString CLIENT_VERSION = "1.0";
//const QString CLIENT_VERSION = "1.0";

/** The URL to check for new version */
const QString VERSION_CHECKER_URL =
		"http://www.delas.it/public/projects/mtp2lastfm/last_release.php";

/** The url for the Last.fm handshake */
const QString LASTFM_HANDSHAKE = "http://post.audioscrobbler.com/";

/** Parameters of the Last.fm handshaking */
const QString LASTFM_HANDSHAKE_PARAMS =
		"?hs=true&p=1.2.1&c=%1&v=%2&u=%3&t=%4&a=%5";

/** All the possible Last.fm response values */
class lastfm_responses
{
	public:
	/** OK response */
	static const int OK      = 1;
	/** This client version has been banned from the server */
	static const int BANNED  = 2;
	/** Authentication details provided were incorrect */
	static const int BADAUTH = 3;
	/** Timestamp provided was not close enough to the current time */
	static const int BADTIME = 4;
	/** General error */
	static const int FAILED  = 5;
};

#endif // CONFIG_H
