#ifndef VERSIONCHECKER_H
#define VERSIONCHECKER_H

#include <QThread>
#include <QtNetwork>
#include <QtXml>

class VersionChecker : public QThread
{
	Q_OBJECT

	public:
	VersionChecker(const QString& current_version,
				   const QString& version_info_url,
				   QObject *parent = 0);
	~VersionChecker();

	protected:
	void run();

	signals:
	void updateVersionLabels(const QString&, const QString&, const QString&);

	private slots:
	void httpDone(bool error);

	private:
	QString m_version_info_url;
	QString m_current_version;
	QHttp* m_http;
	QBuffer* m_buffer;
};

#endif // VERSIONCHECKER_H
