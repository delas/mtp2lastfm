#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <libmtp.h>

using std::string;

/**
 * This is the class that represent a single track, that is a single
 * scrobblable item.
 */
class track
{
	private:
	string m_track_title;  /**< The track title */
	string m_track_artist; /**< The track author (band or single artist) */
	string m_album_title;  /**< The track album */
	int m_pos_on_album;    /**< The position of the track in the album */
	int m_sec_length;      /**< The track length in seconds */
	int m_play_count;      /**< The total track plays counter */

	public:
	
	/**
	 * This is the constructor from a libmtp track
	 *
	 * @param track the libmtp track element
	 */
	track(LIBMTP_track_t* track);

	/**
	 * This method return the track title
	 *
	 * @return the track title
	 */
	inline string getTitle() const { return m_track_title; };

	/**
	 * This method return the track author
	 *
	 * @return the track author
	 */
	inline string getArtist() const { return m_track_artist; };

	/**
	 * This method return the album title
	 *
	 * @return the album title
	 */
	inline string getAlbumTitle() const { return m_album_title; };

	/**
	 * This method return the position of the track on the album
	 *
	 * @return the position of the track
	 */
	inline int getPositionOnAlbum() const { return m_pos_on_album; };

	/**
	 * This method return the length of the track in seconds
	 *
	 * @return the track length
	 */
	inline int getLength() const { return m_sec_length; };
};

#endif // TRACK_H

