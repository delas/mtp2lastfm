#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <QThread>
#include <QtXml>
#include "../view/configurationloading.h"
#include "../view/mainwindow.h"
#include "../db/sqliteorm.h"
#include "../db/base_sql_structure.h"
#include "../model/dbconfig.h"
#include "../model/track.h"

/**
 *
 * @author Andrea Burattin
 */
class LoaderThread : public QThread
{
	Q_OBJECT

	public:
	LoaderThread(const QString& db_path,
				 const QString& old_xml_file_path,
				 QObject *parent = 0);

	protected:
	/**
	 * Thread body
	 */
	void run();

	signals:
	/**
	 * This signal is emitted to send update informations
	 *
	 * @param action a string to describe the in progress action
	 * @param steps new, percentual, of completed job
	 */
	void updateProgress(const QString& action, int steps);
	void startMain();

	private:
	QString m_db_path;
	QString m_old_xml_file_path;
	ConfigurationLoading* m_configurationloading;
	MainWindow* m_mainwindow;
};

#endif // LOADERTHREAD_H
