#include "mainwindow.h"
#include "../threads/loaderthread.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(LoaderThread* loader, QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindowClass)
{
	ui->setupUi(this);
	setWindowTitle(windowTitle().append(" ").append(CLIENT_VERSION));

	/* center the application */
	setGeometry(
			QApplication::desktop()->width()/2 - width()/2,
			QApplication::desktop()->height()/2 - height()/2,
			width(),
			height());

	/* connect the loader */
	mt_loader = loader;
	connect(mt_loader, SIGNAL(startMain()),
			this, SLOT(startMain()));

	/* connect the version update checker */
	mt_vc = new VersionChecker(CLIENT_VERSION, VERSION_CHECKER_URL, 2, this);
	connect(mt_vc, SIGNAL(updateVersionLabels(const QString&, const QString&,
										   const QString&, const QString&)),
			this, SLOT(updateVersionLabels(const QString&, const QString&,
										   const QString&, const QString&)));
	mt_vc->start();

	/* connect the device poller */
	m_devicelist = new QList<device>();
	mt_devicepooler = new DevicePoller(this, m_devicelist, 30, this);
	connect(mt_devicepooler, SIGNAL(deviceListRefresh(QDeviceList*)),
			this, SLOT(deviceListRefresh(QDeviceList*)));
	connect(mt_devicepooler, SIGNAL(startingDeviceRefresh()),
			this, SLOT(startingDeviceRefresh()));
	connect(mt_devicepooler, SIGNAL(deviceRefreshDone()),
			this, SLOT(deviceRefreshDone()));
	mt_devicepooler->start();


	m_scrobbled_tracks = new QStandardItemModel(this);
	m_to_scrobble_tracks = new QStandardItemModel(this);

	ui->scrobbledTree->setModel(m_scrobbled_tracks);
	ui->toScrobbleTree->setModel(m_to_scrobble_tracks);
	updateTracksListsHeader();
}


MainWindow::~MainWindow()
{
	delete ui;
	delete mt_loader;
	delete mt_vc;
	delete m_scrobbled_tracks;
	delete m_devicelist;
}


void MainWindow::updateTracksListsHeader()
{
	/* setting header label */
	QStringList scrobbled_header, to_scrobble_header;
	scrobbled_header.append(tr("Artist"));
	scrobbled_header.append(tr("Track title"));
	scrobbled_header.append(tr("Album title"));
	scrobbled_header.append(tr("Scrobble"));

	to_scrobble_header.append(tr("Artist"));
	to_scrobble_header.append(tr("Track title"));
	to_scrobble_header.append(tr("Album title"));
	to_scrobble_header.append(tr("To scrobble"));

	m_scrobbled_tracks->setHorizontalHeaderLabels(scrobbled_header);
	m_to_scrobble_tracks->setHorizontalHeaderLabels(to_scrobble_header);
}


void MainWindow::updateScrobbledTracksLists()
{
	qDebug("MainWindow : Updating scrobble track list");
	QList<QStandardItem*> row;

	/* clean old rows */
	m_scrobbled_tracks->clear();

	updateTracksListsHeader();

	/* scrobbled track */
	QList<Track> t = Track::getScrobbled();
	for (int i = 0; i < t.size(); i++)
	{
		row.clear();
		row.append(new QStandardItem(t[i].getArtist()));
		row.append(new QStandardItem(t[i].getTitle()));
		row.append(new QStandardItem(t[i].getAlbum()));
		row.append(new QIntItem(t[i].getScrobbleDone()));
		m_scrobbled_tracks->appendRow(row);

		m_scrobbled_tracks->item(i, 3)->setData(t[i].getScrobbleDone());
		m_scrobbled_tracks->item(i, 3)->setTextAlignment(Qt::AlignRight);
		m_scrobbled_tracks->item(i, 0)->setTextAlignment(Qt::AlignRight);
	}
	ui->scrobbledTree->sortByColumn(0, Qt::AscendingOrder);
	qDebug("MainWindow : Scrobble track list updating complete");
}


void MainWindow::updateToScrobbleTracksLists()
{
	qDebug("MainWindow : Updating to scrobble track list");
	QList<QStandardItem*> row;

	/* clean old row */
	m_to_scrobble_tracks->clear();

	updateTracksListsHeader();

	/* tracks to be scrobbled */
	QList<Track> t = Track::getToScrobble();
	for (int i = 0; i < t.size(); i++)
	{
		row.clear();
		row.append(new QStandardItem(t[i].getArtist()));
		row.append(new QStandardItem(t[i].getTitle()));
		row.append(new QStandardItem(t[i].getAlbum()));
		row.append(new QIntItem(t[i].getScrobbleLeft()));
		m_to_scrobble_tracks->appendRow(row);
		m_to_scrobble_tracks->item(i, 3)->setData(t[i].getScrobbleLeft());
		m_to_scrobble_tracks->item(i, 3)->setTextAlignment(Qt::AlignRight);
		m_to_scrobble_tracks->item(i, 0)->setTextAlignment(Qt::AlignRight);
	}
	ui->toScrobbleTree->sortByColumn(0, Qt::AscendingOrder);
	qDebug("MainWindow : To scrobble track list updating complete");
}


void MainWindow::updateVersionLabels(const QString& version,
									 const QString& date,
									 const QString& note,
									 const QString& url)
{
	NewVersionDialog* d = new NewVersionDialog(version, date, note, url, this);
	d->show();
}


void MainWindow::startMain()
{
	show();
}


void MainWindow::deviceListRefresh(QDeviceList* devicelist)
{
	m_devicelist = devicelist;
	ui->devicesCombo->clear();
	for (int i = 0; i < devicelist->size(); i++)
	{
		QString devicename = QString("%1 [%2]")
							 .arg(devicelist->at(i).getName())
							 .arg(devicelist->at(i).getModel());
		ui->devicesCombo->addItem(devicename, "");
	}
}


void MainWindow::startingDeviceRefresh()
{
	ui->devicesCombo->setEnabled(false);
	ui->importButton->setEnabled(false);
}


void MainWindow::deviceRefreshDone()
{
	ui->devicesCombo->setEnabled(true);
	ui->importButton->setEnabled(ui->devicesCombo->count() > 0);
}


void MainWindow::on_actionRefreshLists_triggered()
{
	updateScrobbledTracksLists();
	updateToScrobbleTracksLists();
}


void MainWindow::on_actionScrobble_triggered()
{
	mt_scrobbler = new Scrobbler(this);
	mt_scrobbler->start();
}


void MainWindow::on_actionSetAuthenticationData_triggered()
{
	AuthenticationDialog* ad = new AuthenticationDialog(this);
	ad->show();
}


void MainWindow::on_importButton_clicked()
{
	if (ui->devicesCombo->count() > 0)
	{
		int element = ui->devicesCombo->currentIndex();
		qDebug("MainWindow : Importing from device number %d", element);

		mt_tracksimporter = new TracksImporter(m_devicelist->at(element), this);
		mt_tracksimporter->start();
	}
}


void MainWindow::on_actionExit_triggered()
{
	QApplication::quit();
}
