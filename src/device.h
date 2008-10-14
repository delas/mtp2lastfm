#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include <libmtp.h>
#include "track.h"

#include <iostream>

using std::string;
using std::vector;

/**
 * This class models a single MTP device object
 */
class device
{
	private:
	string m_friendly_name;
	LIBMTP_mtpdevice_t m_libmtp_obj;

	public:
	/**
	 * This is the main constructor, from a libmtp device structure
	 *
	 * @param device the libmtp device structure
	 */
	device(LIBMTP_mtpdevice_t device);

	/**
	 * This method return the current device friendly name
	 *
	 * @return the device name
	 */
	inline string getName() const { return m_friendly_name; };

	/**
	 * This method extracts the track list from the current device
	 *
	 * @return a vector of tracks
	 */
	vector<track> getTrackList();

	/**
	 * This method fetches all the currently connected devices and allow you to
	 * decide which to use
	 *
	 * @return a device list vector
	 */
	static vector<device> getAllConnectedDevices();
};

#endif // DEVICE_H
