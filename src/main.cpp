/*
 * main.cpp -- project main file
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

#include <iostream>
#include <vector>
#include <getopt.h>

#include "track.h"
#include "device.h"
#include "scrobbler.h"

#define print(x) cout << x << endl;
#define verbose(x) if (flag_verbose_mode > 0) print(x)
#define vverbose(x) if (flag_verbose_mode > 1) print(x)

using namespace std;


void help(const char* cmd)
{
	/* header */
	print("mtp2lastfm " << VERSION)
	print("")
	/* help content */
	print("Basic usages: " << cmd << " [options]")
	print("Options:")
	print("  -i, --import        Import all the player track, and mark as already scrobbled")
	print("  -l, --list-devices  List all connected devices")
	print("  -s, --stats         Print some statistics")
	print("  -v, --verbose       Verbose mode (-vv for more verbose)")
	print("  -V, --version       Version information")
	print("  -h, --help          Display this information")
	print("")
}

void version()
{
	/* header */
	print("mtp2lastfm " << VERSION)
	print("")
	/* version content */
	print("Copyright (C) 2008 - Andrea Burattin")
	print("")
	print("This program comes with NO WARRANTY, to the extent permitted by law.")
	print("You may redistribute copies of this program under the terms of")
	print("the GNU General Public License.")
}

void callback(int current, int total)
{
	if (current % 10 == 0)
	{
		cout << endl << current << " of " << total << endl;
	}
	else
	{
		cout << ".";
	}
	cout.flush();
}


int main(int argc, char* argv[])
{
	bool flag_only_import = false; /* sets if just import the songs */
	bool flag_only_list_device = false; /* sets if just list devices */
	bool flag_only_stats = false; /* sets if just show some stats */
	int flag_verbose_mode = 0; /* how much verbose (actually only 2 levels)? */

	/* command line parsing */
	int c;
	int option_index = 0; /* getopt_long stores the option index here */
	static const struct option long_options[] = {
		{"help",         no_argument, 0, 'h'},
		{"import",       no_argument, 0, 'i'},
		{"list-devices", no_argument, 0, 'l'},
		{"stats",        no_argument, 0, 's'},
		{"verbose",      no_argument, 0, 'v'},
		{"version",      no_argument, 0, 'V'},
		{ 0, 0, 0, 0 }
	};
	while ((c = getopt_long(argc, argv, "hilsvV",
	                        long_options, &option_index)) != -1)
	{
		switch (c)
		{
			case 'h':
				help(argv[0]);
				return 0;
			case 'i':
				flag_only_import = true;
				break;
			case 'l':
				flag_only_list_device = true;
				break;
			case 's':
				flag_only_stats = true;
				break;
			case 'v':
				flag_verbose_mode++;
				break;
			case 'V':
				version();
				return 0;
			default:
				return 1;
		}
	}


	/* base objects */
	vverbose("Internal objects declaration")
	string configfile = (string(getenv("HOME")) + "/.mtp2lastfm");
	device d;
	vverbose("Internal objects successfully decleared and initialized")

	/* list all connected device */
	if (flag_only_list_device)
	{
		verbose("Getting all connected devices");
		vector<device> vd = device::getAllConnectedDevices();
		vverbose("All device successfully gotten")

		if (vd.size() == 0)
		{
			print("No devices connected!")
		}
		else
		{
			print("Device list:")
			for (unsigned int i = 0; i < vd.size(); i++)
			{
				vverbose("   Getting device information")
				print(i << ". " << vd[i].getName() << " - " << vd[i].getManufacturer())
			}
		}
		return 0;
	}

	/* load the default scrobbler */
	verbose("Default scrobbler configuration loading");
	scrobbler s = scrobbler::load(configfile);
	vverbose("Default scrobbler successfully loaded")

	/* print some stats */
	if (flag_only_stats)
	{
		vverbose("Getting scrobbled track list")
		const vector<track>& scrobbled = s.getScrobbledTrack();
		if (scrobbled.size() > 0)
		{
			int total_plays = 0;
			int total_secs = 0;
			for (unsigned int i = 0; i < scrobbled.size(); i++)
			{
				total_plays += scrobbled[i].getPlayCount();
				total_secs += scrobbled[i].getLength()*scrobbled[i].getPlayCount();
			}
			vverbose("Scrobbled track list gotten")
			print("Statistics:")
			print(" - " << scrobbled.size() << " listened songs")
			print(" - " << total_plays << " total listenings")
			print(" - about " << (int)(total_plays/scrobbled.size()) << " listenings per song")
			print(" - " << (int)(total_secs/60) << " minute")
		}
		else
		{
			print("No listenings yet")
		}
		return 0;
	}

	/* set up device to be used */
	verbose("Getting all connected devices");
	vector<device> vd = device::getAllConnectedDevices();
	vverbose("All device successfully gotten")
	if (vd.size() == 0)
	{
		print("No devices connected!")
		print("Connect an MTP device and try again...")
		return 1;
	}
	else if (vd.size() == 1)
	{
		verbose("Just one device detected")
		d = vd[0];
	}
	else
	{
		int selected_device = -1;
		do
		{
			print("Device list:")
			for (unsigned int i = 0; i < vd.size(); i++)
			{
				vverbose("   Getting device information")
				print(i << ". " << vd[i].getName() << " - " << vd[i].getManufacturer())
			}
			cout << "Insert the device number [0-" << (vd.size()-1) << "]: ";
			cin >> selected_device;
		} while (selected_device < 0 || (unsigned int)(selected_device) >= vd.size());
		/* we can assign the correct device number... */
		d = vd[selected_device];
	}

	/* the user want to import the song data */
	if (flag_only_import)
	{
		print("Preparing for importing data...")
		verbose("Fetching data from device...")
		s.fetch(d);
		vverbose("Data fetched")
		verbose("Importing data...")
		s.import();
		vverbose("Data correctly imported")
		verbose("Saving data...")
		s.save(configfile);
		vverbose("Data saved")
		print("Data correctly imported!")
		return 0;
	}

	/* if here, the user want to scrobble */
	/* check the lastfm account */
	if (s.getUsername() == "")
	{
		print("Last.fm accout not setted yet")
		string username, password;
		cout << "Please insert your Last.fm username: ";
		cin >> username;
		cout << "Now your password: ";
		cin >> password;
		verbose("Setting Last.fm username and password")
		s.setUsername(username);
		s.setPassword(password);
		vverbose("Username and password setted")
		verbose("Saving data...")
		s.save(configfile);
		vverbose("Data saved")
	}

	print("Preparing for importing data...")
	verbose("Fetching data from device...")
	s.fetch(d);
	vverbose("Data fetched")

	verbose("Verifying tracks to be scrobbled")
	const vector<track>& to_scrobble = s.getToScrobbleTrack();
	if (to_scrobble.size() == 0)
	{
		print("Nothing to do here (no tracks to be scrobbled)")
		return 0;
	}
	else
	{
		print(to_scrobble.size() << " tracks to be scrobbled")
	}

	print("Scrobbling started...")
	if (s.scrobble(callback) == lastfm_responses::OK)
	{
		print("Scrobbling complete!")
		verbose("Saving data...")
		s.save(configfile);
		vverbose("Data saved")
		return 0;
	}
	else
	{
		print("Damn! Scrobbling error (listened below)...")
		print(s.getError())
		return 1;
	}
}
