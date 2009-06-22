#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include <QString>
#include <libmtp.h>
#include "track.h"

/**
 * This class models a single MTP device object
 */
class device
{
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
	inline QString getName() const { return m_friendly_name; }

	/**
	 * This method return the device manufacturer name
	 *
	 * @return the device manufacturer name
	 */
	inline QString getManufacturer() const { return m_manufacturer; }

	/**
	 * This method return the device model name
	 *
	 * @return the device model name
	 */
	inline QString getModel() const { return m_model_name; }

	/**
	 * This method extracts the track list from the current device
	 *
	 * @return a vector of tracks
	 */
	QList<Track> getTrackList() const { return m_track_list; }

	/**
	 * This method fetches all the currently connected devices and allow you to
	 * decide which to use
	 *
	 * @return a device list vector
	 */
	static QList<device> getAllConnectedDevices();

	private:
	QString m_friendly_name;           /**< The device "friendly" name */
	QString m_model_name;              /**< The device model name */
	QString m_manufacturer;            /**< The device manufacturer name */
	QList<Track> m_track_list;         /**< The device track list */
	static bool m_libmtp_initialized;  /**< A private flag to know if libmtp are
										   initialized or not */

};

#endif // DEVICE_H
