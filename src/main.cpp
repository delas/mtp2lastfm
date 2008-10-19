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
#include "track.h"
#include "device.h"
#include "scrobbler.h"

#define print(x) cout << x << endl;
#define verbose(x) if (verbose_mode) print(x)

using namespace std;

void help(const char* cmd)
{
	print("Usage: " << cmd << " [options]")
	print("Options:")
	print("  -i, --import        Import all the player track, and mark as already scrobbled")
	print("  -l, --list-devices  List all connected devices")
	print("  -v                  Verbose mode")
	print("  --help              Display this information")
	print("")
}

int main(int argc, char* argv[])
{
	bool only_import = false;
	bool only_list_device = false;
	bool verbose_mode = false;
	string configfile = (string(getenv("HOME")) + "/.mtp2lastfm");
	device d;

	/* header */
	print("mtp2lastfm v." << CLIENT_VERSION)
	print("================")
	print("")

	/* parameters */
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-i")==0 || strcmp(argv[i], "--import")==0)
		{
			only_import = true;
		}
		if (strcmp(argv[i], "-l")==0 || strcmp(argv[i], "--list-devices")==0)
		{
			only_list_device = true;
		}
		if (strcmp(argv[i], "-v")==0)
		{
			verbose_mode = true;
		}
		else if (strcmp(argv[i], "--help")==0)
		{
			help(argv[0]);
			return 0;
		}
	}

	/* list all connected device */
	if (only_list_device)
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
