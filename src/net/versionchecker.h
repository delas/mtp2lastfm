#ifndef VERSIONCHECKER_H
#define VERSIONCHECKER_H

#include <QThread>
#include <QtNetwork>
#include <QtXml>
#include <QDebug>

/**
 * This is the class that allow to check if there is a new version of the
 * software, connecting to a webpage, and parsing its output.
 *
 * @author Andrea Burattin
 */
class VersionChecker : public QThread
{
	Q_OBJECT

	public:
	/**
	 * Base thread constructor, the destination file, must be in this XML
	 * format:
	 * <code>
	 *   &lt;release&gt;
	 *     &lt;version&gt;1.1&lt;/version&gt;
	 *     date&gt;Feb 3rd, 2009&lt;/date&gt;
	 *     &lt;note&gt;Some notes&lt;/note&gt;
	 *  &lt;/release&gt;
	 * </code>
	 *
	 * @param current_version the current version string
	 * @param version_info_url URL of the file with the information
	 * @param delay seconds to wait before start connection
	 * @param parent parent object
	 */
	VersionChecker(const QString& current_version,
				   const QString& version_info_url,
				   int delay = 2,
				   QObject *parent = 0);

	/**
	 * Default destructor
	 */
	~VersionChecker();

	protected:
	/**
	 * Thread body
	 */
	void run();

	signals:
	/**
	 * This signal is emitted if the thread finds a new release
	 *
	 * @param remote_version the new version available
	 * @param remote_date the date of the new release
	 * @param remote_note some note in the new release
	 * @param remote_url the URL to download the new release
	 */
	void updateVersionLabels(const QString& remote_version,
							 const QString& remote_date,
							 const QString& remote_note,
							 const QString& remote_url);

	private slots:
	/**
	 * Slot to capture the end of the HTTP transaction
	 *
	 * @param error is some error occurs
	 */
	void httpDone(bool error);

	private:
	int m_delay;
	QString m_version_info_url;
	QString m_current_version;
	QHttp* m_http;
	QBuffer* m_buffer;
};

#endif // VERSIONCHECKER_H
