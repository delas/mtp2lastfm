#include "scrobbler.h"
#include<iostream>

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
	temp = "a[" + cur + "]=" + track.getArtist() + "&" +
	       "t[" + cur + "]=" + track.getTitle() + "&" +
	       "i[" + cur + "]=" + toString(play_timestamp) + "&" +
	       "o[" + cur + "]=P&" +
	       "r[" + cur + "]=" + "&" +
	       "l[" + cur + "]=" + toString(track.getLength()) + "&" +
	       "b[" + cur + "]=" + track.getAlbumTitle() + "&" +
	       "n[" + cur + "]=" + toString(track.getPositionOnAlbum()) + "&" +
	       "m[" + cur + "]=" + "&";
	return temp;
}


void scrobbler::setUsername(const string& username)
{
	m_username = username;
}


void scrobbler::setPassword(const string& password)
{
	m_password = MD5String(const_cast<char*>(password.c_str()));
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
				for (int j = 0; j < playcount - t.getPlayCount(); j++)
				{
					m_to_scrobble.push_back(t);
				}
			}
		}
		else
		{
			/* this track has never been scrobbled (and listened?) */
			if (vt[i].getPlayCount() > 0)
			{
				for (int j = 0; j < vt[i].getPlayCount(); j++)
				{
					m_to_scrobble.push_back(vt[i]);
				}
			}
		}
	}
}


int scrobbler::scrobble()
{
	lastfm_handshake();

	string param = "s=" + m_session_id + "&";
	int using_timestamp = timestamp() - m_to_scrobble.size()*AVG_SONG_LENGTH;
	int scrobbled_items = 0;

	while (!m_to_scrobble.empty())
	{
		if (scrobbled_items == LASTFM_MAX_TRACK_PER_SCROBBLE - 1)
		{
			/* reached the max number of scrobbleable track */
			string out;
			std::cout << "Scrobbling...\n";
			std::cout.flush();
			out = httpRequest(m_session_url, param);
			std::cout << out;
			if (out != "OK")
			{
				return lastfm_responses::FAILED;
			}

			/* reset some values */
			scrobbled_items = 0;
			param = "s=" + m_session_id + "&";
		}
		else
		{
			/* we can add some tracks to the scrobbling session */
			track t = m_to_scrobble.back();
			m_to_scrobble.pop_back();
			param += getSubmissionPost(i,
		                               using_timestamp + i*AVG_SONG_LENGTH,
		                               t);
			scrobbled_items++;

			/* now, add this track to the scrobbled ones */
			vector<track>::iterator element;
			element = find(m_scrobbled.begin(), m_scrobbled.end(), t);
			if (element == m_scrobbled.end())
			{
				/* add the new track with play counter set to 1 */
				t.setPlayCount(1);
				m_scrobbled.push_back(t);
			}
			else
			{
				/* increase the play counter by 1 */
				element->setPlayCount(element->getPlayCount() + 1);
			}
		}
	}

	return lastfm_responses::OK;
}


bool scrobbler::save(const string& filename, const scrobbler& obj)
{
	ofstream output_file (filename.c_str(),
	                      ofstream::out|ofstream::binary|ofstream::trunc);
	int obj_dimension = sizeof(scrobbler) +
	                    sizeof(track) * (obj.m_scrobbled.size() +
	                                     obj.m_to_scrobble.size());
	if (output_file.is_open())
	{
		output_file.write((const char*)&obj, obj_dimension);
		output_file.close();
		return true;
	}
	return false;
}


scrobbler scrobbler::load(const string& filename)
{
	scrobbler s;
	ifstream input_file (filename.c_str(), ifstream::binary);
	if (input_file.is_open())
	{
		input_file.read((char*)&s, scrobbler::getFileSize(filename));
		input_file.close();
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
