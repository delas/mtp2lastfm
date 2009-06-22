#ifndef DEVICEPOLLER_H
#define DEVICEPOLLER_H

#include <QThread>
//#include "../view/mainwindow.h"
#include "../model/device.h"
#include "../model/track.h"

class MainWindow;
typedef QList<device> QDeviceList;

Q_DECLARE_METATYPE(QDeviceList);

/**
 *
 * @author Andrea Burattin
 */
class DevicePoller : public QThread
{
	Q_OBJECT

	public:
	DevicePoller(MainWindow* mainwindow, QDeviceList* devicelist,
				 int delay = 30, QObject *parent = 0);

	protected:
	/**
	 * Thread body
	 */
	void run();

	signals:
	/**
	 * This signal is emitted when a new device is recognized
	 *
	 * @param devicelist the new devices list
	 */
	void deviceListRefresh(QDeviceList* devicelist);
	void startingDeviceRefresh();
	void deviceRefreshDone();

	private:
	MainWindow* m_mainwindow;
	QDeviceList* m_devicelist;
	int m_delay;
};

#endif // DEVICEPOLLER_H
