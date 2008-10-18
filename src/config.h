#include <string>

using std::string;

/** The client identifier */
const string CLIENT_ID = "tst";

/** The current client version */
const string CLIENT_VERSION = "1.0";

/** The user agent used for the cURL calls */
const string USER_AGENT =
"Mozilla/5.0 (X11; U; Linux i686; it; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5";

/** Average song length (used to simulate the "listening") */
const int AVG_SONG_LENGTH = 130; /* seconds */

/** The url for the Last.fm handshake */
const string LASTFM_HANDSHAKE =
     "http://post.audioscrobbler.com/?hs=true&p=1.2.1&c=%s&v=%s&u=%s&t=%s&a=%s";

/** The path for the mtp2lastfm.xsd */
const string MTP2LASTFM_XSD_URI =
                         "http://mtp2lastfm.sourceforge.net/xsd/mtp2lastfm.xsd";

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
