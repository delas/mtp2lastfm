/*
 * config.h -- project configuration file
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

#include <string>

using std::string;

/** The client identifier */
const string CLIENT_ID = "mtp";

/** The current client version */
const string VERSION = "0.1";

/** The user agent used for the cURL calls */
const string USER_AGENT =
"Mozilla/5.0 (X11; U; Linux i686; it; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5";

/** Average song length (used to simulate the "listening") */
const int AVG_SONG_LENGTH = 130; /* seconds */

/** The url for the Last.fm handshake */
const string LASTFM_HANDSHAKE =
     "http://post.audioscrobbler.com/?hs=true&p=1.2.1&c=%s&v=%s&u=%s&t=%s&a=%s";

/** The path for the mtp2lastfm.xsd */
const string MTP2LASTFM_XSD_URI =
                         "http://mtp2lastfm.sourceforge.net/xsd/mtp2lastfm.xsd";

/** All the possible Last.fm response values */
class lastfm_responses
{
	public:
	/** OK response */
	static const int OK      = 1;
	/** This client version has been banned from the server */
	static const int BANNED  = 2;
	/** Authentication details provided were incorrect */
	static const int BADAUTH = 3;
	/** Timestamp provided was not close enough to the current time */
	static const int BADTIME = 4;
	/** General error */
	static const int FAILED  = 5;
};
