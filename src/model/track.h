#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <libmtp.h>
#include "../db/sqliteorm.h"

/**
 * This is the class that represent a single track, that is a single
 * scrobblable item.
 *
 * @author Andrea Burattin
 */
class Track : public SQLiteORM
{
	public:
	/**
	 * This method build a new track object with the specified values. If this
	 * object is not in the
	 *
	 * @param artist the artist name
	 * @param title the track title
	 * @return the required track
	 */
	static Track get(const QString& artist, const QString& title);

	/**
	 * This method fetches all the tracks already scrobbled
	 *
	 * @return a track objects list
	 */
	static QList<Track> getScrobbled();

	/**
	 * This method fetches all the tracks to be scrobbled
	 *
	 * @return a track objects list
	 */
	static QList<Track> getToScrobble();

	/**
	 * This method counts the tracks to be scrobbled
	 *
	 * @param list the list of tracks to be scrobbled
	 * @return the number of scrobbling
	 */
	static int getToScrobbleCount(QList<Track> list);

	/**
	 * This is the constructor from a libmtp track
	 *
	 * @param track the libmtp track element
	 */
	Track(LIBMTP_track_t* track);

	/**
	 * This method gets the album title
	 *
	 * @return the album title
	 */
	QString getAlbum() const;

	/**
	 * This method gets the track position in the album
	 *
	 * @return the track position
	 */
	int getAlbumPosition() const;

	/**
	 * This method gets the artist name
	 *
	 * @return the artist name
	 */
	QString getArtist() const;

	/**
	 * This method gets the fist time this track has been added
	 *
	 * @return the first time the track has been added
	 */
	QDateTime getFirstAdd() const;

	/**
	 * This method gets the last time this track has been scrobbled
	 *
	 * @return the last scrobbled time
	 */
	QDateTime getLastScrobble() const;

	/**
	 * This method gets the number of scrobbles done for this track
	 *
	 * @return the number of scrobble done
	 */
	int getScrobbleDone() const;

	/**
	 * This method gets the number of scrobble left for this track
	 *
	 * @return the number of scrobbles left
	 */
	int getScrobbleLeft() const;

	/**
	 * This method gets the length of the track, in seconds
	 *
	 * @return the track length
	 */
	int getLength() const;

	/**
	 * This method gets the track title
	 *
	 * @return the track title
	 */
	QString getTitle() const;

	/**
	 * This method sets the album title
	 *
	 * @param album the album title
	 */
	void setAlbum(const QString& album);

	/**
	 * This method sets the track position in the album
	 *
	 * @param album_position the track position
	 */
	void setAlbumPosition(int album_position);

	/**
	 * This method sets the artist name
	 *
	 * @param artist the artist name
	 */
	void setArtist(const QString& artist);

	/**
	 * This method sets the track length
	 *
	 * @param seconds the track length, in seconds
	 */
	void setLength(int seconds);

	/**
	 * This method sets the scrobble already done
	 *
	 * @param scrobble_done the scrobble done
	 */
	void setScrobbleDone(int scrobble_done);

	/**
	 * With this method you can set the total number of listening done and,
	 * automatically, will update the scrobble left counter.
	 *
	 * @param listening the total number of track listenings
	 */
	void setTotalListenings(int listening);

	/**
	 * This method sets the track title
	 *
	 * @param title the track title
	 */
	void setTitle(const QString& title);

	/**
	 * This method sets the scrobble times
	 *
	 * @param times number os scrobble done for the track
	 */
	void scrobbled(int times);


	private:
	/**
	 * Private, empty constructor
	 */
	Track();

	void buildStructure();
};

#endif // DBCONFIG_H
