#ifndef SCROBBLER_H
#define SCROBBLER_H

#include <string.h>
#include "track.h"

using std::string;

/**
 * This is the Last.fm track scrobbler
 */
class scrobbler
{
	private:
	string m_username;    /**< The Last.fm account username */
	string m_password;    /**< The MD5 of the Last.fm account password */
	string m_session_id;  /**< The submissions session id */
	string m_session_url; /**< The submissions URL for this session */
};

#endif // SCROBBLER_H
