#include "devicepoller.h"

DevicePoller::DevicePoller(MainWindow* mainwindow, QDeviceList* devicelist,
						   int delay, QObject *parent)
		: QThread(parent)
{
	qRegisterMetaType<QDeviceList>("QDeviceList"); /* required to signal */

	m_devicelist = devicelist;
	m_mainwindow = mainwindow;
	m_delay = delay;
}


void DevicePoller::run()
{
	do
	{
		qDebug("DevicePoller : Starting device refreshing");
		emit startingDeviceRefresh();
		QList<device> devicelist = device::getAllConnectedDevices();
		int old_size = m_devicelist->size();
		int new_size = devicelist.size();

		if (new_size != old_size)
		{
			*m_devicelist = devicelist;
			qDebug("DevicePoller : Different devices, view has to refresh (old: %d, new %d)!", old_size, new_size);
			emit deviceListRefresh(m_devicelist);
		}
		emit deviceRefreshDone();
		qDebug("DevicePoller : Device refreshing done, go to sleep");
		sleep(m_delay);
	} while (true);
}
