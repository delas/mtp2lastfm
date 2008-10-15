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


class lastfm_responses
{
	public:
	static const int OK      = 1;
	static const int BANNED  = 2;
	static const int BADAUTH = 3;
	static const int BADTIME = 4;
	static const int FAILED  = 5;
};
