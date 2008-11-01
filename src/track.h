/*
 * track.h -- track header file
 *
 * Author: Andrea Burattin (http://www.delas.it)
 * Copyright (C) 2008  Andrea Burattin
 *
 * $Id$
 */

/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 *                   MA  02111-1307, USA.
 */

#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <libmtp.h>
#include "utils.h"
#include "xsd/mtp2lastfm.h"

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
	 * This is the constructor from a XML track
	 *
	 * @param track the XML track element
	 */
	track(xml::track track);

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

	/**
	 * This method return the number of times the track has been played
	 *
	 * @return the total play counter
	 */
	inline int getPlayCount() const { return m_play_count; };

	/**
	 * This method sets the number of times the track has been played
	 *
	 * @param total_play_count the total number of plays of this track
	 */
	void setPlayCount(int total_play_count);

	/**
	 * This method tells you if a track can be scrobbled (i.e. if all the
	 * required filed are filled).
	 *
	 * @return true if the track is scrobblable, false otherwise
	 */
	bool isScrolleable() const;

	/**
	 * Equal operator overloading
	 *
	 * @return true if the tracks have the same title and artist, false
	 *         otherwise
	 */
	bool operator==(const track& other);

	/**
	 * Not equal operator overloading
	 *
	 * @return false if the tracks have the same title and artist, true
	 *         otherwise
	 */
	bool operator!=(const track& other);
};

#endif // TRACK_H

