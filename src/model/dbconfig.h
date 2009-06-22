#ifndef DBCONFIG_H
#define DBCONFIG_H

#include <QString>
#include "../db/sqliteorm.h"

/**
 * This class is useful to get and set default program configuration values into
 * the database.
 *
 * @author Andrea Burattin
 */
class DBConfig : public SQLiteORM
{
	public:
	/**
	 * This method fetches a configuration from the database. If this
	 * configuration is not yet initialized, creates and returns it.
	 *
	 * @param name the configuration name
	 * @return the configuration object
	 */
	static DBConfig get(const QString& name);

	/**
	 * This method gets the configuration value.
	 *
	 * @return the configuration value
	 */
	QString value();

	/**
	 * This method sets the configuration value.
	 *
	 * @param value the configuration value
	 */
	void value(const QString& value);


	private:
	DBConfig();


	protected:
	void buildStructure();
};

#endif // DBCONFIG_H
