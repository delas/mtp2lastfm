#include "track.h"

Track::Track()
		: SQLiteORM()
{
	buildStructure();
}


Track Track::get(const QString& artist, const QString& title)
{
	Track t;
	QString where_condition = QString("`title` = \"%1\" AND `artist` = \"%2\"")
							  .arg(title)
							  .arg(artist);

	QList<SQLiteORM> tracks = t.getAll(where_condition, "");
	if (tracks.size() == 0)
	{
		t.setArtist(artist);
		t.setTitle(title);
		t.m_fields["first_add"].first = QDateTime::currentDateTime();
		t.m_fields["last_scrobble"].first = QDateTime::currentDateTime();
		t.m_fields["scrobble_left"].first = 0;
		t.save();
	}
	else
	{
		t.assignValue(tracks[0]);
	}
	return t;
}


void Track::buildStructure()
{
	setTableName("tracks");

	addModelDescriptor("id", NUMERIC);
	addModelDescriptor("album", TEXT);
	addModelDescriptor("album_position", NUMERIC);
	addModelDescriptor("artist", TEXT);
	addModelDescriptor("first_add", TEXT);
	addModelDescriptor("last_scrobble", TEXT);
	addModelDescriptor("scrobble_done", NUMERIC);
	addModelDescriptor("scrobble_left", NUMERIC);
	addModelDescriptor("secs_length", NUMERIC);
	addModelDescriptor("title", TEXT);

	setPrimaryKeyFieldName("id");
}


QString Track::getAlbum() const
{
	return getField("artist").toString();
}


int Track::getAlbumPosition() const
{
	return getField("album_position").toInt();
}


QString Track::getArtist() const
{
	return getField("artist").toString();
}


QDateTime Track::getFirstAdd() const
{
	return getField("first_add").toDateTime();
}


QDateTime Track::getLastScrobble() const
{
	return getField("last_scrobble").toDateTime();
}


int Track::getScrobbleDone() const
{
	return getField("scrobble_done").toInt();
}


int Track::getScrobbleLeft() const
{
	return getField("scrobble_left").toInt();
}


int Track::getLength() const
{
	return getField("secs_length").toInt();
}


QString Track::getTitle() const
{
	return getField("title").toString();
}


void Track::setAlbum(const QString& album)
{
	setFieldValue("album", album);
}


void Track::setAlbumPosition(int album_position)
{
	setFieldValue("album_position", album_position);
}


void Track::setArtist(const QString& artist)
{
	setFieldValue("artist", artist);
}


void Track::setLength(int seconds)
{
	setFieldValue("secs_length", seconds);
}


void Track::setScrobbleDone(int scrobble_done)
{
	setFieldValue("scrobble_done", scrobble_done);
}


void Track::setTotalListenings(int listening)
{
	int scrobble_done = getScrobbleDone();
	if (listening > scrobble_done)
	{
		setFieldValue("scrobble_done", scrobble_done);
		setFieldValue("scrobble_left", listening - scrobble_done);
	}
}


void Track::setTitle(const QString& title)
{
	setFieldValue("title", title);
}
