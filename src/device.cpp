#include "device.h"

device::device(LIBMTP_mtpdevice_t device)
{
	m_libmtp_obj = device;
	m_friendly_name = LIBMTP_Get_Friendlyname(&m_libmtp_obj);
}


vector<track> device::getTrackList()
{
	vector<track> to_return;

	LIBMTP_track_t *tracks;
	LIBMTP_Init();
	std::cout<< "asd\n"; std::cout.flush();
	tracks = LIBMTP_Get_Tracklisting_With_Callback(&m_libmtp_obj, NULL, NULL);
	std::cout<< "asd\n"; std::cout.flush();
	if (tracks != NULL)
	{
		std::cout<< "asd\n"; std::cout.flush();
		LIBMTP_track_t *track_, *tmp;
		track_ = tracks;
		while (track_ != NULL)
		{
			track t(track_);
			to_return.push_back(t);
			tmp = track_;
			track_ = track_->next;
			LIBMTP_destroy_track_t(tmp);
		}
	}

	return to_return;
}


vector<device> device::getAllConnectedDevices()
{
	vector<device> to_return;

	LIBMTP_mtpdevice_t *device_list, *iter;
	LIBMTP_Init();

	LIBMTP_Get_Connected_Devices(&device_list);
	for (iter = device_list; iter != NULL; iter = iter->next)
	{
		device d(*iter);
		to_return.push_back(d);
	}

	LIBMTP_Release_Device_List(device_list);

	return to_return;
}
