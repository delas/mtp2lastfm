#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <QThread>
#include <QtXml>
#include "../view/configurationloading.h"
#include "../db/sqliteorb.h"
#include "../db/base_sql_structure.h"

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

	private:
	QString m_db_path;
	QString m_old_xml_file_path;
	ConfigurationLoading* m_configurationloading;
};

#endif // LOADERTHREAD_H
