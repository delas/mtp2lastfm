#ifndef SCROBBLER_H
#define SCROBBLER_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <curl/curl.h>

#include "config.h"
#include "track.h"
#include "device.h"
#include "md5.h"
#include "utils.h"

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

/**
 * This is the Last.fm track scrobbler
 */
class scrobbler
{
	private:
	string m_username;           /**< The Last.fm account username */
	string m_password;           /**< The MD5 of the Last.fm account password */
	string m_session_id;         /**< The submissions session id */
	string m_session_url;        /**< The submissions URL for this session */
	public:
	vector<track> m_scrobbled;   /**< A list of already-scrobbled track */
	vector<track> m_to_scrobble; /**< A list of track to scrobble */

	private:
	int lastfm_handshake();
	string httpRequest(const string& url, const string& post ="");
	size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp);
	string getSubmissionPost(const string& artist, const string& title, int play_timestamp, int duration, int current_sumbit) const;

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

	/**
	 * This method fetches the data from the device and populate the
	 * m_to_scrobble vector with the correct data (checking the already
	 * scrobbled file and, eventually adding with the difference of the played
	 * times)
	 *
	 * @param device the device from where the data have to be fetched
	 */
	void fetch(const device& device);

	int scrobble();

	/**
	 * This method saves a general scrobbler class into a binary file
	 *
	 * @param filename the file where to save the object
	 * @param obj      the scrobbler object
	 * @return true if the saving processing has correctly finished, false
	 *         otherwise
	 */
	static bool save(const string& filename, const scrobbler& obj);

	/**
	 * This method saves a general scrobbler class into a binary file
	 *
	 * @param filename the file where to save the object
	 * @param obj      the scrobbler object
	 * @return the scrobbler object from the loaded file
	 */
	static scrobbler load(const string& filename);

	/**
	 * This function return the file size
	 *
	 * @param filename image binary dump file name
	 * @return the total number of bytes in the file
	 */
	static int getFileSize(const string& filename);
};

#endif // SCROBBLER_H
