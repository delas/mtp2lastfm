#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QDesktopWidget>
#include "newversiondialog.h"
#include "../net/versionchecker.h"
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

	public slots:
	void updateVersionLabels(const QString&, const QString&,
							 const QString&, const QString&);
	void startMain();

	private:
	Ui::MainWindowClass *ui;
	LoaderThread* m_loader;
	VersionChecker* vc;
};

#endif // MAINWINDOW_H
