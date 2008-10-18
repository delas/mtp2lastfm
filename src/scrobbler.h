#ifndef SCROBBLER_H
#define SCROBBLER_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <curl/curl.h>
#include "config.h"
#include "track.h"
#include "device.h"
#include "md5.h"
#include "utils.h"
#include "xsd/mtp2lastfm.hxx"

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::auto_ptr;

/**
 * This is the Last.fm track scrobbler
 */
class scrobbler
{
	private:
	string m_username;           /**< The Last.fm account username */
	string m_password;           /**< MD5 of the Last.fm account password */
	string m_session_id;         /**< The submissions session id */
	string m_session_url;        /**< The submissions URL for this session */
	vector<track> m_scrobbled;   /**< A list of already-scrobbled track */
	vector<track> m_to_scrobble; /**< A list of track to scrobble */

	private:
	/**
	 * This method performs an HTTP cURL request
	 *
	 * @param url  the url destination of the request
	 * @param post the data to be POSTed (or en empty string if no data)
	 * @return the output data
	 */
	string httpRequest(const string& url, const string& post ="");

	/**
	 * This method starts the submission session, with the default Last.fm
	 * handshake protocol
	 *
	 * @see lastfm_responses
	 * @see http://www.last.fm/api/submissions#handshake
	 * @return a handshake response value
	 */
	int lastfm_handshake();

	/**
	 * This methods simplifies the creation of the post string, compiling all
	 * the variables required by Last.fm protocol for the submission of a
	 * track.
	 *
	 * @see http://www.last.fm/api/submissions#subs
	 * @param current_sumbit an increasing integer
	 * @param play_timestamp the timestamp when the song play begin
	 * @param track          the track to be submitted
	 * @return a Last.fm-correct post variables string
	 */
	string getSubmissionPost(int current_sumbit,
	                         int play_timestamp,
	                         const track& track) const;

	/**
	 * This method increases the times a track has been scrobbled (by summing 1
	 * or adding the new track)
	 *
	 * @param t the track that has been scrobbled another time
	 */
	void increaseScrobbledCount(track& t);

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
	 * @param password the Last.fm password
	 */
	void setPassword(const string& password);

	/**
	 * This method sets the Last.fm account password MD5 hash.
	 *
	 * @param passwordHash the Last.fm password hash
	 */
	void setPasswordHash(const string& passwordHash);

	/**
	 * This method fetches the data from the device and populate the
	 * m_to_scrobble vector with the correct data (checking the already
	 * scrobbled file and, eventually adding with the difference of the played
	 * times)
	 *
	 * @param device the device from where the data have to be fetched
	 */
	void fetch(const device& device);

	/**
	 * This method scrobbles all the track fetched
	 *
	 * @return a scrobble response value
	 */
	int scrobble();

	/**
	 * This method yust mark all the track to be scrobbled, without doing it
	 * really
	 */
	void import();

	/**
	 * This method saves a general scrobbler class into a binary file
	 *
	 * @param filename the file where to save the object
	 * @param obj      the scrobbler object
	 * @return true if the saving processing has correctly finished, false
	 *         otherwise
	 */
	bool save(const string& filename);

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
