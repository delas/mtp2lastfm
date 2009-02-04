#ifndef BASE_SQL_STRUCTURE_H
#define BASE_SQL_STRUCTURE_H

#include <QString>

/**
 * Database tables creation
 */
const QString SQL_CREATE_TABLES =
		"CREATE TABLE config ("
			"id INTEGER PRIMARY KEY, "
			"name TEXT, "
			"value TEXT"
		");"
		"CREATE TABLE tracks ("
			"album TEXT, "
			"album_position NUMERIC, "
			"artist TEXT, "
			"first_add NUMERIC, "
			"id INTEGER PRIMARY KEY, "
			"last_scrobble NUMERIC, "
			"scrobble_done NUMERIC, "
			"scrobble_left NUMERIC, "
			"secs_length NUMERIC, "
			"title TEXT"
		");";

/**
 * Database default fields
 */
const QString SQL_BASE_INSERT =
		"INSERT INTO config (name, value) VALUES (\"DB_VERSION\", \"1.0\");"
		"INSERT INTO config (name) VALUES (\"LASTFM_USERNAME\");"
		"INSERT INTO config (name) VALUES (\"LASTFM_PASSHASH\");";

#endif // BASE_SQL_STRUCTURE_H
