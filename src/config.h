#include <string>

using std::string;

/**
 * The client identifier
 */
const string CLIENT_ID = "tst";
/**
 * The current client version
 */
const string CLIENT_VERSION = "1.0";

/**
 * The url for the Last.fm handshake
 */
const string LASTFM_HANDSHAKE =
	"http://post.audioscrobbler.com/?hs=true&p=1.2.1&c=%s&v=%s&u=%s&t=%s&a=%s";
