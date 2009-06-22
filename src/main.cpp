#include <QtGui/QApplication>
#include <iostream>
#include "config.h"
#include "threads/loaderthread.h"

#define print(x) std::cout << x << std::endl;


void help(const char* appName, const char* db_path)
{
	print("mtp2lastfm " << CLIENT_VERSION.toStdString())
	print("")
	print("Usage: " << appName << " [OPTION] [FILE]")
	print("")
	print("Options:")
	print("  -V, --version       Version information")
	print("  -h, --help          Display this information")
	print("")
	print("If you want to import your previously configuration (from mtp2lastfm 0.1.*) you")
	print("have to remove the file " << db_path << " and then use:")
	print("")
	print(appName << " OLD_MTP2LASTFM_FILE")
	print("")
}


void version()
{
	/* header */
	print("mtp2lastfm " << CLIENT_VERSION.toStdString())
	print("")
	/* version content */
	print("Copyright (C) 2009 - Andrea Burattin")
	print("")
	print("This program comes with NO WARRANTY, to the extent permitted by law.")
	print("You may redistribute copies of this program under the terms of")
	print("the GNU General Public License.")
}


int main(int argc, char *argv[])
{
	QString param;
//	QString db_path(getenv("HOME"));
//	db_path = db_path.append("/.mtp2lastfm.db");
	QString db_path("mtp2lastfm.db");

	if (argc > 1)
	{
		param = QString(argv[1]);
		if (param == "--help" || param == "-h")
		{
			help(argv[0], db_path.toStdString().c_str());
			return 0;
		}
		if (param == "--version" || param == "-V")
		{
			version();
			return 0;
		}
	}

	QApplication a(argc, argv);
	LoaderThread* lt = new LoaderThread(db_path, param);
	lt->start();
	return a.exec();
}
