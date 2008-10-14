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
