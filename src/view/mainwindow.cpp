#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
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
}


MainWindow::~MainWindow()
{
	delete ui;
}
