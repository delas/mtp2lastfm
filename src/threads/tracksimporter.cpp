#include "tracksimporter.h"

TracksImporter::TracksImporter(const device& device, QObject *parent)
		: QThread(parent), m_device(device)
{
	m_tracksimport = new TracksImport(this);
	m_tracksimport->show();

	qDebug("TracksImporter : New thread created");
}


void TracksImporter::run()
{
	qDebug("TracksImporter : Thread started");

	QList<Track> list = m_device.getTrackList();
	int size = list.size();
	int current;

	for (int i = 0; i < size; i++)
	{
		current = (i+1)*100/size;
		QString label = tr("Importing track %1 of %2...")
						.arg(i)
						.arg(size);
		emit updateProgress(label, current);

		list[i].save();
	}

	emit updateProgress(tr("Importing complete!"), 100);
	qDebug("TracksImporter : Thread finished");
}
