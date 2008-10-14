#include <iostream>
#include <vector>
#include "track.h"
#include "device.h"
#include "scrobbler.h"

using namespace std;

int main()
{
	vector<device> vd = device::getAllConnectedDevices();
	device d = vd[0];

	cout << "Scrobbling " << d.getName() << ":" << endl;
	cout << "..." << endl;
}
