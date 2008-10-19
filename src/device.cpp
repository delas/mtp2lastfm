/*
 * device.cpp -- device functions
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

#include "device.h"

bool device::m_libmtp_initialized = false;


device::device()
{}


device::device(LIBMTP_mtpdevice_t* device)
{
	device::checkLibmtpInitialization();
	m_friendly_name = LIBMTP_Get_Friendlyname(device);
	m_manufacturer = LIBMTP_Get_Manufacturername(device);

	LIBMTP_track_t *tracks;
	tracks = LIBMTP_Get_Tracklisting_With_Callback(device, NULL, NULL);
	if (tracks != NULL)
	{
		LIBMTP_track_t *track_, *tmp;
		track_ = tracks;
		while (track_ != NULL)
		{
			track t(track_);
			m_track_list.push_back(t);
			tmp = track_;
			track_ = track_->next;
			LIBMTP_destroy_track_t(tmp);
		}
	}
}


vector<device> device::getAllConnectedDevices()
{
	device::checkLibmtpInitialization();
	vector<device> to_return;

	LIBMTP_mtpdevice_t* device_list, *iter;
	LIBMTP_Get_Connected_Devices(&device_list);

	for (iter = device_list; iter != NULL; iter = iter->next)
	{
		device d(iter);
		to_return.push_back(d);
	}
	LIBMTP_Release_Device_List(device_list);

	return to_return;
}

void device::checkLibmtpInitialization()
{
	if (!device::m_libmtp_initialized)
	{
		LIBMTP_Init();
		device::m_libmtp_initialized = true;
	}
}
