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
	m_loader = loader;
	connect(m_loader, SIGNAL(startMain()),
		this, SLOT(startMain()));

	/* connect the version update checker */
	vc = new VersionChecker(CLIENT_VERSION, VERSION_CHECKER_URL, 2, this);
	connect(vc, SIGNAL(updateVersionLabels(const QString&, const QString&,
										   const QString&, const QString&)),
			this, SLOT(updateVersionLabels(const QString&, const QString&,
										   const QString&, const QString&)));
	vc->start();
}


MainWindow::~MainWindow()
{
	delete ui;
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
