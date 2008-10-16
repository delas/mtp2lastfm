#include <iostream>
#include <vector>
#include "track.h"
#include "device.h"
#include "scrobbler.h"

using namespace std;

int main()
{
	string user, pass;

	cout << "Username: "; cin >> user;
	cout << "Password: "; cin >> pass;

	scrobbler s;
	s.setUsername(user);
	s.setPassword(pass);

	vector<device> vd = device::getAllConnectedDevices();
	device d = vd[0];

	s.fetch(d);
	cout << "Scrobbling " << d.getName() << ":" << endl;
	s.scrobble();
}
