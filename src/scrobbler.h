#ifndef SCROBBLER_H
#define SCROBBLER_H

#include <string>
#include <vector>
#include "config.h"
#include "track.h"
#include "md5.h"

using std::string;
using std::vector;

/**
 * This is the Last.fm track scrobbler
 */
class scrobbler
{
	private:
	string m_username;         /**< The Last.fm account username */
	string m_password;         /**< The MD5 of the Last.fm account password */
	string m_session_id;       /**< The submissions session id */
	string m_session_url;      /**< The submissions URL for this session */
	vector<track> m_scrobbled; /**< A list of already-scrobbled track */

	public:
	/**
	 * This method sets the Last.fm account username
	 *
	 * @param username the Last.fm username
	 */
	void setUsername(const string& username);

	/**
	 * This method sets the Last.fm account password.
	 *
	 * This password is immediately hashed in MD5, and so the original one is
	 * forever lost. This as a security issue (there is no real need to store
	 * the true real password).
	 *
	 * @param username the Last.fm password
	 */
	void setPassword(const string& password);
};

#endif // SCROBBLER_H
