#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QDesktopWidget>
#include <QStandardItemModel>
#include <QFlags>
#include "newversiondialog.h"
#include "authenticationdialog.h"
#include "../net/versionchecker.h"
#include "../threads/devicepoller.h"
#include "../threads/tracksimporter.h"
#include "../threads/scrobbler.h"
#include "../model/qintitem.h"
#include "../config.h"

namespace Ui
{
	class MainWindowClass;
}
class LoaderThread;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
	MainWindow(LoaderThread* loader, QWidget *parent = 0);
	~MainWindow();

	void updateScrobbledTracksLists();
	void updateToScrobbleTracksLists();
	void updateTracksListsHeader();

	public slots:
	void updateVersionLabels(const QString&, const QString&,
							 const QString&, const QString&);

	/**
	 * Slot to catch a new device list
	 */
	void deviceListRefresh(QDeviceList* devicelist);

	/**
	 * Slot to catch the device list fetching start
	 */
	void startingDeviceRefresh();

	/**
	 * Slot to catch the device list fetching end
	 */
	void deviceRefreshDone();

	void startMain();
	void on_actionRefreshLists_triggered();
	void on_actionScrobble_triggered();
	void on_actionSetAuthenticationData_triggered();
	void on_importButton_clicked();
	void on_actionExit_triggered();

	private:
	Ui::MainWindowClass *ui;

	LoaderThread* mt_loader;
	VersionChecker* mt_vc;
	DevicePoller* mt_devicepooler;
	TracksImporter* mt_tracksimporter;
	Scrobbler* mt_scrobbler;

	QStandardItemModel* m_scrobbled_tracks;
	QStandardItemModel* m_to_scrobble_tracks;
	QDeviceList* m_devicelist;
};

#endif // MAINWINDOW_H
