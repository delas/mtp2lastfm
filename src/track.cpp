#include "track.h"

track::track(LIBMTP_track_t* track)
{
	if (track->title != NULL)
	{
		m_track_title = track->title;
	}
	if (track->artist != NULL)
	{
		m_track_artist = track->artist;
	}
	if (track->album != NULL)
	{
		m_album_title = track->album;
	}
	m_pos_on_album = track->tracknumber;
	m_sec_length = track->duration / 1000; /* duration is in milliseconds */
	m_play_count = track->usecount;
}


track::track(xml::track track)
{
	m_track_title = track.title();
	m_track_artist = track.artist();
	m_album_title = track.album();
	m_pos_on_album = track.albumPosition();
	m_sec_length = track.length();
	m_play_count = track.playCount();
}


void track::setPlayCount(int total_play_count)
{
	if (total_play_count > 0)
	{
		m_play_count = total_play_count;
	}
}


bool track::operator==(const track& other)
{
	bool result;
	result = (m_track_title == other.getTitle() &&
	          m_track_artist == other.getArtist());
	return result;
}


bool track::operator!=(const track& other)
{
	return !(*this == other);
}
