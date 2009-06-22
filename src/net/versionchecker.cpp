#include "versionchecker.h"
#include "../view/mainwindow.h"


VersionChecker::VersionChecker(const QString& current_version,
							   const QString& version_info_url,
							   int delay,
							   QObject *parent)
		: QThread(parent)
{
	m_current_version = current_version;
	m_version_info_url = version_info_url;
	m_delay = delay;
	m_http = new QHttp(this);
	m_buffer = new QBuffer(this);
	m_buffer->open(QIODevice::ReadWrite);

	connect(m_http, SIGNAL(done(bool)),
			this, SLOT(httpDone(bool)));
}


VersionChecker::~VersionChecker()
{
	if (m_http)
	{
		m_http->close();
		delete m_http;
	}
	if (m_buffer)
	{
		m_buffer->close();
		delete m_buffer;
	}
}


void VersionChecker::run()
{
	sleep(m_delay);
	QUrl url(m_version_info_url);
	QByteArray path = url.path().toAscii();

	/* add extra info to url */
	QString os ("Unknown");

#if defined(Q_OS_MACX)
	os = "Mac OS X";
#elif defined(Q_OS_MAC9)
	os = "Mac OS 9";
#elif defined(Q_OS_MSDOS)
	os = "MS-DOS and Windows";
#elif defined(Q_OS_OS2)
	os = "OS/2";
#elif defined(Q_OS_OS2EMX)
	os = "XFree86 on OS/2 (not PM)";
#elif defined(Q_OS_WIN32)
	os = "Win32 (Windows 95/98/ME and Windows NT/2000/XP)";
#elif defined(Q_OS_CYGWIN)
	os = "Cygwin";
#elif defined(Q_OS_SOLARIS)
	os = "Sun Solaris";
#elif defined(Q_OS_HPUX)
	os = "HP-UX";
#elif defined(Q_OS_ULTRIX)
	os = "DEC Ultrix";
#elif defined(Q_OS_LINUX)
	os = "Linux";
#elif defined(Q_OS_FREEBSD)
	os = "FreeBSD";
#elif defined(Q_OS_NETBSD)
	os = "NetBSD";
#elif defined(Q_OS_OPENBSD)
	os = "OpenBSD";
#elif defined(Q_OS_BSDI)
	os = "BSD/OS";
#elif defined(Q_OS_IRIX)
	os = "SGI Irix";
#elif defined(Q_OS_OSF)
	os = "HP Tru64 UNIX";
#elif defined(Q_OS_SCO)
	os = "SCO OpenServer 5";
#elif defined(Q_OS_UNIXWARE)
	os = "UnixWare 7, Open UNIX 8";
#elif defined(Q_OS_AIX)
	os = "AIX";
#elif defined(Q_OS_HURD)
	os = "GNU Hurd";
#elif defined(Q_OS_DGUX)
	os = "DG/UX";
#elif defined(Q_OS_RELIANT)
	os = "Reliant UNIX";
#elif defined(Q_OS_DYNIX)
	os = "DYNIX/ptx";
#elif defined(Q_OS_QNX)
	os = "QNX";
#elif defined(Q_OS_QNX6)
	os = "QNX RTP 6.1";
#elif defined(Q_OS_LYNX)
	os = "LynxOS";
#elif defined(Q_OS_BSD4)
	os = "BSD 4.4 system";
#elif defined(Q_OS_UNIX)
	os = "UNIX BSD/SYSV system";
#endif

	path.append("?os=").append(os);
	path.append("&version=").append(m_current_version);

	m_http->setHost(url.host());
	m_http->get(path, m_buffer);
	qDebug("VersionChecker : Remote request submitted");
}


void VersionChecker::httpDone(bool errors)
{
	m_buffer->close();

	if (!errors)
	{
		qDebug("VersionChecker : Connection established");
		QDomDocument doc;
		if(doc.setContent(m_buffer->data()))
		{
			QString remote_version = doc.elementsByTagName("version").item(0)
									 .toElement().text();
			QString remote_date = doc.elementsByTagName("date").item(0)
								  .toElement().text();
			QString remote_note = doc.elementsByTagName("note").item(0)
								  .toElement().text();
			QString remote_url = doc.elementsByTagName("download").item(0)
								  .toElement().text();
			qDebug("VersionChecker : Remote version: %s", remote_version.toStdString().c_str());

			if (remote_version != m_current_version)
			{
				emit updateVersionLabels(remote_version,
										 remote_date,
										 remote_note,
										 remote_url);
			}
		}
	}
	else
	{
		qDebug("VersionChecker : Connection error");
	}
}
