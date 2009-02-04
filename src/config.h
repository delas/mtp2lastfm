#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

/** The client identifier */
const QString CLIENT_ID = "mtp";

/** The current client version */
const QString CLIENT_VERSION = "1.0-prealpha";

/** The user agent used for the cURL calls */
const QString USER_AGENT =
"Mozilla/5.0 (X11; U; Linux i686; it; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5";

/** Average song length (used to simulate the "listening") */
const int AVG_SONG_LENGTH = 130; /* seconds */

/** The url for the Last.fm handshake */
const QString LASTFM_HANDSHAKE =
	 "http://post.audioscrobbler.com/?hs=true&p=1.2.1&c=%1&v=%2&u=%3&t=%4&a=%5";

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
