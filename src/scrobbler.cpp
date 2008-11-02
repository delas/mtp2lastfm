/*
 * scrobbler.cpp -- scrobbler functions
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

#include "scrobbler.h"

int scrobbler::lastfm_handshake()
{
	/* get the timestamp */
	string timestamp_ = toString(timestamp());

	/* generate the token */
	string to_token = m_password + timestamp_;
	char* chr_token = MD5String((char*)to_token.c_str());
	string token(chr_token);

	/* generate the complete url */
	char* chr_url = new char[512];
	sprintf(chr_url, LASTFM_HANDSHAKE.c_str(),
	    CLIENT_ID.c_str(),
	    CLIENT_VERSION.c_str(),
	    m_username.c_str(),
	    timestamp_.c_str(),
	    token.c_str());
	string url(chr_url);

	/* start the handshake process */
	vector<string> param = explode("\n", httpRequest(url));

	if (param[0] == "OK")
	{
		m_session_id = param[1];
		m_session_url = param[3];
		return lastfm_responses::OK;
	} else if (param[0] == "BANNED")
	{
		return lastfm_responses::BANNED;
	} else if (param[0] == "BADAUTH")
	{
		return lastfm_responses::BADAUTH;
	} else if (param[0] == "BADTIME")
	{
		return lastfm_responses::BADTIME;
	} else if (param[0] == "FAILED")
	{
		return lastfm_responses::FAILED;
	}
	return lastfm_responses::FAILED;
}


string html_buffer; /**< The data fetched from the web calling */
size_t writeHTML (char* buffer, size_t size, size_t nmemb, void* userp)
{
  html_buffer = string(buffer);
  return size * nmemb;
}


string scrobbler::httpRequest(const string& url, const string& post)
{
	CURL* curl_handle;

	curl_handle = curl_easy_init();
	if(curl_handle)
	{
		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, USER_AGENT.c_str());
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writeHTML);
		if (post != "")
		{
			curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post.c_str());
		}
		curl_easy_perform(curl_handle);

		/* always cleanup */
		curl_easy_cleanup(curl_handle);
	}
	return html_buffer;
}


string scrobbler::getSubmissionPost(int current_sumbit,
                                    int play_timestamp,
                                    const track& track) const
{
	string temp;
	string cur = toString(current_sumbit);
	temp = "a[" + cur + "]=" + UrlEncodeString(track.getArtist()) + "&" +
	       "t[" + cur + "]=" + UrlEncodeString(track.getTitle()) + "&" +
	       "i[" + cur + "]=" + toString(play_timestamp) + "&" +
	       "o[" + cur + "]=P&" +
	       "r[" + cur + "]=" + "&" +
	       "l[" + cur + "]=" + toString(track.getLength()) + "&" +
	       "b[" + cur + "]=" + UrlEncodeString(track.getAlbumTitle()) + "&" +
	       "n[" + cur + "]=" + toString(track.getPositionOnAlbum()) + "&" +
	       "m[" + cur + "]=" + "&";
	return temp;
}


void scrobbler::setUsername(const string& username)
{
	m_username = username;
}


string scrobbler::getUsername() const
{
	return m_username;
}


void scrobbler::setPassword(const string& password)
{
	m_password = MD5String(const_cast<char*>(password.c_str()));
}


void scrobbler::setPasswordHash(const string& passwordHash)
{
	m_password = passwordHash;
}


string scrobbler::getError() const
{
	return m_last_error;
}


void scrobbler::fetch(const device& device)
{
	vector<track> vt = device.getTrackList();
	vector<track>::iterator element;
	int playcount;
	for (unsigned int i = 0; i < vt.size(); i++)
	{
		playcount = vt[i].getPlayCount();
		element = find(m_scrobbled.begin(), m_scrobbled.end(), vt[i]);
		if (element != m_scrobbled.end())
		{
			/* this track has already been scrobbled (how many times?) */
			if (element->getPlayCount() < playcount)
			{
				/* we need to scrobble this track some times */
				track& t = *element;
				/* is this track able to be scrobbled? */
				if (t.isScrolleable())
				{
					for (int j = 0; j < playcount - t.getPlayCount(); j++)
					{
						m_to_scrobble.push_back(t);
					}
				}
			}
		}
		else
		{
			/* this track has never been scrobbled (and listened?) */
			if (vt[i].getPlayCount() > 0)
			{
				/* is this track able to be scrobbled? */
				if (vt[i].isScrolleable())
				{
					for (int j = 0; j < vt[i].getPlayCount(); j++)
					{
						m_to_scrobble.push_back(vt[i]);
					}
				}
			}
		}
	}
}


int scrobbler::scrobble(void (*callback)(int current, int total, scrobbler* const s))
{
	lastfm_handshake();
	srand((unsigned)time(0)); /* randomizer */

	string param, out;
	int total_to_scrobble = m_to_scrobble.size();
	int using_timestamp = timestamp() - total_to_scrobble;
	int scrobbled_items = 0;
	int curr_track_position = -1;

	while (!m_to_scrobble.empty())
	{
		/* take every track in random order */
		curr_track_position = rand() % m_to_scrobble.size();
		track t = m_to_scrobble[curr_track_position];

		param = "s=" + m_session_id + "&" +
			getSubmissionPost(0, using_timestamp, t);
		out = httpRequest(m_session_url, param);

		if (out == "BADSESSION\n")
		{
			lastfm_handshake();
		} else if (out == "OK\n")
		{
			using_timestamp += 1;
			scrobbled_items++;
			m_to_scrobble.erase(m_to_scrobble.begin() + curr_track_position);
			increaseScrobbledCount(t);
			if (callback != 0)
			{
				callback(scrobbled_items, total_to_scrobble, this);
			}
		} else {
			m_last_error = out;
			m_last_error += "\n" + t.getTitle()
			             +  "\n" + t.getArtist()
			             +  "\n" + t.getAlbumTitle()
			             +  "\n"
			             +  "\n" + "Scrobbling URL:"
			             +  "\n" + m_session_url
			             +  "\n" + "Scrobbling param:"
			             +  "\n" + param
			             +  "\n";
			return lastfm_responses::FAILED;
		}
	}
	return lastfm_responses::OK;
}


void scrobbler::import()
{
	for (unsigned int i = 0; i < m_to_scrobble.size(); i++)
	{
		increaseScrobbledCount(m_to_scrobble[i]);
	}
	m_to_scrobble.clear();
}


const vector<track>& scrobbler::getScrobbledTrack() const
{
	return m_scrobbled;
}


const vector<track>& scrobbler::getToScrobbleTrack() const
{
	return m_to_scrobble;
}


void scrobbler::increaseScrobbledCount(track& t)
{
	vector<track>::iterator element;
	element = find(m_scrobbled.begin(), m_scrobbled.end(), t);
	if (element != m_scrobbled.end())
	{
		/* this track has already been scrobbled */
		element->setPlayCount(element->getPlayCount() + 1);
	}
	else
	{
		/* this track has never been scrobbled */
		t.setPlayCount(1);
		m_scrobbled.push_back(t);
	}
}


bool scrobbler::save(const string& filename)
{
	/* the lastfm authentication data */
	xml::lastfm x_lastfm(m_username, m_password);

	/* tracks already scrobbled */
	xml::scrobbled x_scrobbled;
	xml::scrobbled::track_sequence x_scrobbled_track;
	for (unsigned int i = 0; i < m_scrobbled.size(); i++)
	{
		xml::track t(m_scrobbled[i].getTitle(),
		             m_scrobbled[i].getArtist(),
		             m_scrobbled[i].getAlbumTitle(),
		             m_scrobbled[i].getPositionOnAlbum(),
		             m_scrobbled[i].getLength(),
		             m_scrobbled[i].getPlayCount());
		x_scrobbled_track.push_back(t);
	}
	x_scrobbled.track(x_scrobbled_track);

	/* tracks to be scrobbled */
	xml::toScrobble x_toscrobble;
	xml::toScrobble::track_sequence x_toscrobble_track;
	for (unsigned int i = 0; i < m_to_scrobble.size(); i++)
	{
		xml::track t(m_to_scrobble[i].getTitle(),
		             m_to_scrobble[i].getArtist(),
		             m_to_scrobble[i].getAlbumTitle(),
		             m_to_scrobble[i].getPositionOnAlbum(),
		             m_to_scrobble[i].getLength(),
		             m_to_scrobble[i].getPlayCount());
		x_toscrobble_track.push_back(t);
	}
	x_toscrobble.track(x_toscrobble_track);

	/* merge all the data to the root element */
	xml::mtp2lastfm x_root(x_lastfm, x_scrobbled, x_toscrobble);


	xml_schema::namespace_infomap map;
	map[""].name = "";
	map[""].schema = MTP2LASTFM_XSD_URI;

	/* write it out */
	ofstream output_file (filename.c_str(), ofstream::out|ofstream::trunc);
	if (output_file.is_open())
	{
		xml::mtp2lastfm_ (output_file, x_root, map);
		output_file.close();
		return true;
	}
	return false;
}


scrobbler scrobbler::load(const string& filename)
{
	scrobbler s;
	try
	{
		auto_ptr<xml::mtp2lastfm> x = xml::mtp2lastfm_(filename,
		                                           xml_schema::flags::keep_dom);

		/* load the lastfm data */
		xml::lastfm& lfm = x->lastfm();
		s.setUsername(lfm.username());
		s.setPasswordHash(lfm.passwordMd5Hash());

		/* load the scrobbled tracks */
		xml::scrobbled& scrobb = x->scrobbled();
		for (xml::scrobbled::track_const_iterator t (scrobb.track().begin());
			t != scrobb.track().end(); t++)
		{
			track tr(*t);
			s.m_scrobbled.push_back(tr);
		}

		/* load the to-be-scrobbled tracks */
		xml::toScrobble& to_scrobb = x->toScrobble();
		for (xml::toScrobble::track_const_iterator t(to_scrobb.track().begin());
			t != to_scrobb.track().end(); t++)
		{
			track tr(*t);
			int tot_listenings = tr.getPlayCount();
			tr.setPlayCount(1);
			for (int i = 0; i < tot_listenings; i++)
			{
				s.m_to_scrobble.push_back(tr);
			}
		}
	}
	catch (const xml_schema::exception& e)
	{
	}
	return s;
}


int scrobbler::getFileSize(const string& filename)
{
	long begin,end;
	ifstream input_file (filename.c_str(), ifstream::binary);
	begin = input_file.tellg();
	input_file.seekg (0, std::ios::end);
	end = input_file.tellg();
	input_file.close();
	return end-begin;
}
