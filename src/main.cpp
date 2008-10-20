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
#define verbose(x) if (flag_verbose_mode) print(x)

using namespace std;


void help(const char* cmd)
{
	/* header */
	print("mtp2lastfm " << CLIENT_VERSION)
	print("")
	/* help content */
	print("Basic usages: " << cmd << " [options]")
	print("Options:")
	print("  -i, --import        Import all the player track, and mark as already scrobbled")
	print("  -l, --list-devices  List all connected devices")
	print("  -v, --verbose       Verbose mode")
	print("  -V, --version       Version information")
	print("  -h, --help          Display this information")
	print("")
}

void version()
{
	/* header */
	print("mtp2lastfm " << CLIENT_VERSION)
	print("")
	/* version content */
	print("Copyright (C) 2008 - Andrea Burattin")
	print("")
	print("This program comes with NO WARRANTY, to the extent permitted by law.")
	print("You may redistribute copies of this program under the terms of")
	print("the GNU General Public License.")
}


int main(int argc, char* argv[])
{
	bool flag_only_import = false;
	bool flag_only_list_device = false;
	bool flag_verbose_mode = false;

	/* command line parsing */
	int c;
	int option_index = 0; /* getopt_long stores the option index here */
	static const struct option long_options[] = {
		{"help",         no_argument, 0, 'h'},
		{"import",       no_argument, 0, 'i'},
		{"list-devices", no_argument, 0, 'l'},
		{"verbose",      no_argument, 0, 'v'},
		{"version",      no_argument, 0, 'V'},
		{ 0, 0, 0, 0 }
	};
	while ((c = getopt_long(argc, argv, "hilvV",
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
			case 'v':
				flag_verbose_mode = true;
				break;
			case 'V':
				version();
				return 0;
			default:
				return 1;
		}
	}

	/* base objects */
	verbose("Internal objects declaration")
	string configfile = (string(getenv("HOME")) + "/.mtp2lastfm");
	device d;

	/* list all connected device */
	if (flag_only_list_device)
	{
		verbose("Getting all connected devices");
		vector<device> vd = device::getAllConnectedDevices();
		print("Device list")
		print("-----------");
		if (vd.size() == 0)
		{
			print("No devices present.")
		}
		else
		{
			for (unsigned int i = 0; i < vd.size(); i++)
			{
				print(i << ". " << vd[i].getName() << " - " << vd[i].getManufacturer())
			}
		}
		print("");
		return 0;
	}

	/* load the default scrobbler */
	verbose("Default scrobbler configuration load");
	scrobbler s = scrobbler::load(configfile);

	/* set up device to be used */
	verbose("Getting all connected devices");
	vector<device> vd = device::getAllConnectedDevices();
	if (vd.size() == 1)
	{
		d = vd[0];
	}

	if (s.getUsername() == "")
	{
		verbose("Last.fm accout not setted")
		
	}

// 	string user, pass;

// 	cout << "Username: "; cin >> user;
// 	cout << "Password: "; cin >> pass;
// 	scrobbler s = scrobbler::load("asd.xml");

// 	s.setUsername("delas__test");
// 	s.setPassword("delas__test");

// 	vector<device> vd = device::getAllConnectedDevices();
// 	for (unsigned int i = 0; i < vd.size(); i++)
// 	{
// 		cout << i << ". " << vd[i].getName() << " (" << vd[i].getManufacturer() << ")\n";
// 	}
// 	device d = vd[0];

// 	s.fetch(d);
// 	s.import();
// 	s.save("saved.xml");
// 	cout << "Scrobbling " << d.getName() << ":" << endl;
// 	int response = s.scrobble();
// 	if (response == lastfm_responses::OK)
// 	{
// 		cout << "ok\n";
// 	}
// 	else
// 	{
// 		cout << "errors...\n";
// 		cout << s.getError();
// 	}
// 	s.save("saved.xml");
}
