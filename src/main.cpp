#include <iostream>
#include <vector>
#include "track.h"
#include "device.h"
#include "scrobbler.h"

using namespace std;

int main()
{
	vector<device> vd = device::getAllConnectedDevices();

	for (unsigned int i = 0; i < vd.size(); i++)
	{
		cout << i << ". " << vd[i].getName() << endl;
		vector<track> vt = vd[i].getTrackList();
		for (unsigned int j = 0; j < vt.size(); j++)
		{
			cout << "   " << j << ". " <<
				vt[j].getTitle() << " - " <<
				vt[j].getArtist() << endl;
		}
	}
}
