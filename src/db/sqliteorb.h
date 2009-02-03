#ifndef SQLITEORB_H
#define SQLITEORB_H

#include <QtSql>
#include <QString>
#include <QHash>
#include <QList>
#include <QPair>

/**
 * This is the base ORM class, providing some basic methods for the object
 * mapping into an SQLite database.
 *
 * @author Andrea Burattin
 */
class SQLiteORM
{
	public:
	/**
	 * The possible types for each table field
	 */
	enum FIELD_TYPE
	{
		TEXT,   /**< A general text field */
		NUMERIC /**< A general numeric field */
	};


	/**
	 * Default, empty constructor
	 */
	SQLiteORM();

	/**
	 * This is the method for the database initialization. It's not a problem to
	 * call this if the database is already open, since it checkes if the
	 * connection is already initialized
	 *
	 * @param db_path the database complete path
	 * @return true if the database is initialized, false otherwise
	 */
	static bool initDB(const QString& db_path);

	/**
	 * This is the static method to shut down all the query to the database
	 */
	static void shutdown();

	/**
	 * This method adds a new field into the table descriptor
	 *
	 * @param field_name the name of the field
	 * @param field_type the type of the field
	 */
	void addModelDescriptor(const QString& field_name, FIELD_TYPE field_type);

	/**
	 * Method to change a field value
	 *
	 * @param field_name field name to be setted
	 * @param field_value field value to be setted
	 * @return boolean true if the operation ends correctly, false otherwise
	 */
	void setFieldValue(const QString& field_name, const QVariant& field_value);

	/**
	 * Method to get a float field value
	 *
	 * @param field_name the field name
	 * @return the field value
	 */
	QVariant getField(const QString& field_name) const;

	/**
	 * Method to set the static WHERE condition
	 *
	 * @param where_condition SQL WHERE condition
	 */
	void setStaticWhereCondition(const QString& where_condition);

	/**
	 * Method to get the static WHERE condition
	 *
	 * @return SQL WHERE condition
	 */
	QString getStaticWhereCondition() const;

	/**
	 * Method to set the table name where the object is mapped, in the database
	 *
	 * @param table_name the table name
	 */
	void setTableName(const QString& table_name);

	/**
	 * Method to get the table name where the object if mapped, in the database
	 *
	 * @return the table name
	 */
	QString getTableName() const;

	/**
	 * Method to set the primary key field name, it has to be an INTEGER and
	 * autoincrement field
	 *
	 * @param primary_key_field_name the field name
	 */
	void setPrimaryKeyFieldName(const QString& primary_key_field_name);

	/**
	 * Method to get the primary key field name
	 *
	 * @return the field name
	 */
	QString getPrimaryKeyFieldName() const;

	/**
	 * Method for object loading from a primary key integer value
	 *
	 * @param element_id primary key value
	 * @return boolean true if the operation ends correctly, false otherwise
	 */
	bool load(int element_id);

	/**
	 * Method to load a set of elements
	 *
	 * @param where_condition SQL where condition, more than the static one
	 * @param ordering SQL ordering statement (e.g. "id DESC")
	 * @param from SQL from value
	 * @param limit the number of elements to fetch
	 * @return an ordered list of elements
	 */
	QList<SQLiteORM> getAll(QString where_condition, QString ordering,
							int from = 0, int limit = 999);

	/**
	 * Method to fisically remove a logic object
	 *
	 * @return true if the object has been removed, false otherwise
	 */
	bool remove();

	/**
	 * Method to fisically save a logic object
	 *
	 * @return true if the object has been saved, false otherwise
	 */
	bool save();

	/**
	 * This method to get the last error, is any
	 *
	 * @return the last error text
	 */
	QString getLastError() const;


	private:
	/**
	 * Method to update an existing logic object
	 *
	 * @return true if the object has been updated, false otherwise
	 */
	bool update();

	/**
	 * Method to build a new logic object
	 *
	 * @return true if the object has been created, false otherwise
	 */
	bool create();

	/* database management */
	static QSqlDatabase m_db;  /**< Database object */
	static QString* m_db_path; /**< Database file path */

	/* ORB base members */
	QString m_table_name;
	QString m_primary_key_field_name;
	QString m_static_where_condition;
	QHash<QString, QPair<QVariant, FIELD_TYPE> > m_fields;
	QString m_last_error;
	bool m_removed; /* Has, the object, been removed? */
	bool m_concretized; /* Has, the object, a database entry? */

};

#endif // SQLITEORB_H
