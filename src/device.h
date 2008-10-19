/*
 * device.h -- device header file
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
	 * This is the default main constructor
	 *
	 */
	device();

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
