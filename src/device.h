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
	string m_friendly_name;           /**< The device "friendly" name */
	string m_manufacturer;            /**< The device manufacturer name */
	vector<track> m_track_list;       /**< The device track list */
	static bool m_libmtp_initialized; /**< A private flag to know if libmtp are
	                                       initialized or not */

	/**
	 * This method checks, and do, libmtp initialization
	 */
	static void checkLibmtpInitialization();

	public:
	/**
	 * This is the main constructor, from a libmtp device structure
	 *
	 * @param device the libmtp device structure
	 */
	device(LIBMTP_mtpdevice_t* device);

	/**
	 * This method return the current device friendly name
	 *
	 * @return the device name
	 */
	inline string getName() const { return m_friendly_name; };

	/**
	 * This method return the device manufacturer name
	 *
	 * @return the device manufacturer name
	 */
	inline string getManufacturer() const { return m_manufacturer; };

	/**
	 * This method extracts the track list from the current device
	 *
	 * @return a vector of tracks
	 */
	inline vector<track> getTrackList() const { return m_track_list; };

	/**
	 * This method fetches all the currently connected devices and allow you to
	 * decide which to use
	 *
	 * @return a device list vector
	 */
	static vector<device> getAllConnectedDevices();
};

#endif // DEVICE_H
