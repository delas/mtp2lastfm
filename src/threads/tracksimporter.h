#ifndef TRACKSIMPORTER_H
#define TRACKSIMPORTER_H

#include <QThread>
#include "../view/tracksimport.h"
#include "../model/device.h"

/**
 *
 * @author Andrea Burattin
 */
class TracksImporter : public QThread
{
	Q_OBJECT

	public:
	TracksImporter(const device& device, QObject *parent = 0);

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

	/**
	 * This signal is emitted when there is an error
	 *
	 * @param error the error description
	 */
	void errorCatched(const QString& error);

	private:
	const device& m_device;
	TracksImport* m_tracksimport;
};

#endif // TRACKSIMPORTER_H
