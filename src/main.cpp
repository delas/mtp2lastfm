#include <QtGui/QApplication>
#include "threads/loaderthread.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	LoaderThread* lt = new LoaderThread("demo.db", "old.xml");
	lt->start();

	return a.exec();
}
