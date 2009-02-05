#include "sqliteorb.h"

/* static members initialization */
QSqlDatabase SQLiteORM::m_db = QSqlDatabase::addDatabase("QSQLITE");
QString* SQLiteORM::m_db_path = 0;


SQLiteORM::SQLiteORM()
{
	m_concretized = false;
	m_removed = true;

	buildStructure();
}


bool SQLiteORM::initDB(const QString& db_path)
{
	if (!m_db_path || *m_db_path != db_path || !m_db.isOpen())
	{
		/* members clean up */
		if (!m_db_path)
		{
			delete m_db_path;
		}
		if (m_db.isOpen())
		{
			m_db.close();
		}

		/* new database path */
		m_db_path = new QString(db_path);
		/* new database */
		m_db.setDatabaseName(db_path);

		/* let's try to open the connection */
		if (!m_db.open())
		{
			return false;
		}
	}
	return true;
}


void SQLiteORM::shutdown()
{
	if (m_db.isOpen())
	{
		m_db.close();
	}
}


int SQLiteORM::getNumberOfDBTables()
{
	if (m_db.isOpen())
	{
		QSqlQuery query;
		bool query_succeed = query.exec("SELECT COUNT(*) FROM sqlite_master")
							 && query.first();
		if (query_succeed)
		{
			return query.value(0).toInt();
		}
		else
		{
			return -1;
		}
	}
	return -1;
}

#include <iostream>
using namespace std;

bool SQLiteORM::execSQL(const QString& sql_query)
{
	if (!m_db.isOpen())
	{
		return false;
	}

	QSqlQuery query;
	query.exec("BEGIN TRANSACTION");
	bool query_succeed = true;
	if (sql_query.contains(";", Qt::CaseInsensitive))
	{
		QStringList sql_queries = sql_query.split(";", QString::SkipEmptyParts);
		QString sql_query_current;
		for (int i = 0; i < sql_queries.size(); i++)
		{
			sql_query_current = sql_queries[i];
			sql_query_current.trimmed();
			if (sql_query_current != "")
			{
				sql_query_current.append(";");
				query_succeed = query.exec(sql_query_current) && query_succeed;
			}
		}
	}
	else
	{
		query_succeed = query.exec(sql_query);
	}
	if (query_succeed)
	{
		query.exec("COMMIT TRANSACTION");
	}
	else
	{
		query.exec("ROLLBACK TRANSACTION");
	}
	query.exec("END TRANSACTION");
	return query_succeed;
}


void SQLiteORM::addModelDescriptor(const QString& field_name,
								   FIELD_TYPE field_type)
{
	if (!m_fields.contains(field_name))
	{
		m_fields[field_name] = QPair<QVariant, FIELD_TYPE>(QVariant(), field_type);
	}
}


void SQLiteORM::setFieldValue(const QString& field_name,
							  const QVariant& field_value)
{
	if (m_fields.contains(field_name))
	{
		m_fields[field_name].first = field_value;
	}
}


QVariant SQLiteORM::getField(const QString& field_name) const
{
	if (m_fields.contains(field_name) && !m_removed)
	{
		return m_fields[field_name].first;
	}
	return QVariant();
}


void SQLiteORM::setStaticWhereCondition(const QString& where_condition)
{
	m_static_where_condition = where_condition;
}


QString SQLiteORM::getStaticWhereCondition() const
{
	return m_static_where_condition;
}


void SQLiteORM::setTableName(const QString& table_name)
{
	m_table_name = table_name;
}


QString SQLiteORM::getTableName() const
{
	return m_table_name;
}


void SQLiteORM::setPrimaryKeyFieldName(const QString& primary_key_field_name)
{
	m_primary_key_field_name = primary_key_field_name;
}


QString SQLiteORM::getPrimaryKeyFieldName() const
{
	return m_primary_key_field_name;
}


bool SQLiteORM::load(int element_id)
{
	QString fields_name;
	QString static_where;

	QList<QString> keys = m_fields.keys();
	int keys_size = keys.size();
	for (int i = 0; i < keys_size; i++)
	{
		fields_name.append(keys[i]);
		if (i < keys_size - 1)
		{
			fields_name.append(", ");
		}
	}

	if (m_static_where_condition != "")
	{
		static_where.append(" AND ").append(m_static_where_condition);
	}

	QString sql_query = QString("SELECT %1 FROM %2 WHERE `%3` = \"%4\" %5")
						.arg(fields_name)
						.arg(m_table_name)
						.arg(m_primary_key_field_name)
						.arg(element_id)
						.arg(static_where);

	QSqlQuery query;
	bool query_succeed = query.exec(sql_query) && query.first();
	if (query_succeed)
	{
		QVariant value;
		for (int i = 0; i < keys_size; i++)
		{
			value = query.value(i);
			if (m_fields[keys[i]].second == TEXT)
			{
				setFieldValue(keys[i], value.toString());
			}
			else if (m_fields[keys[i]].second == NUMERIC)
			{
				setFieldValue(keys[i], value.toDouble());
			}
		}
		m_concretized = true;
		m_removed = false;
	}
	else
	{
		m_last_error = query.lastError().text();
	}
	return query_succeed;
}


QList<SQLiteORM> SQLiteORM::getAll(QString where_condition, QString ordering,
								   int from, int limit)
{
	QList<SQLiteORM> fetched;
	QString fields_name;
	QString sql_ordering;

	QList<QString> keys = m_fields.keys();
	int keys_size = keys.size();
	for (int i = 0; i < keys_size; i++)
	{
		fields_name.append(keys[i]);
		if (i < keys_size - 1)
		{
			fields_name.append(", ");
		}
	}

	if (where_condition != "")
	{
		where_condition.prepend("AND (");
		where_condition.append(")");
	}

	if (m_static_where_condition != "")
	{
		if (where_condition != "")
		{
			where_condition.append(" AND ");
		}
		where_condition
				.append("(")
				.append(m_static_where_condition)
				.append(")");
	}

	if (ordering != "")
	{
		sql_ordering.append("ORDER BY ").append(ordering);
	}

	QString sql_query = QString("SELECT %1 FROM %2 WHERE 1=1 %3 %4 LIMIT %5,%6")
						.arg(fields_name)
						.arg(m_table_name)
						.arg(where_condition)
						.arg(sql_ordering)
						.arg(from)
						.arg(limit);

	QSqlQuery query;
	if (query.exec(sql_query))
	{
		while (query.next())
		{
			SQLiteORM obj;
			obj.m_fields = m_fields;
			for (int i = 0; i < keys_size; i++)
			{
				obj.m_fields[keys[i]].first = query.value(i);
			}
			obj.m_concretized = true;
			obj.m_removed = false;
			fetched.append(obj);
		}
	}
	else
	{
		m_last_error = query.lastError().text();
	}
	return fetched;
}


bool SQLiteORM::remove()
{
	QString sql_query = QString("DELETE FROM `%1` WHERE `%2` = \"%3\"")
						.arg(m_table_name)
						.arg(m_primary_key_field_name)
						.arg(getField(m_primary_key_field_name).toDouble());
	QSqlQuery query;
	query.exec("BEGIN TRANSACTION");
	bool query_succeed = query.exec(sql_query);
	if (query_succeed)
	{
		m_removed = true;
	}
	if (query_succeed)
	{
		query.exec("COMMIT TRANSACTION");
		m_removed = true;
	}
	else
	{
		query.exec("ROLLBACK TRANSACTION");
		m_last_error = query.lastError().text();
	}
	query.exec("END TRANSACTION");
	return query_succeed;
}


bool SQLiteORM::save()
{
	if (!m_concretized || m_removed)
	{
		return create();
	}
	else
	{
		return update();
	}
}


QString SQLiteORM::getLastError() const
{
	return m_last_error;
}


bool SQLiteORM::update()
{
	QString field_setting;
	QList<QString> keys = m_fields.keys();
	int keys_size = keys.size();
	for (int i = 0; i < keys_size; i++)
	{
		QString field = QString("`%1` = \"%2\"")
						.arg(keys[i])
						.arg(m_fields[keys[i]].first.toString());
		field_setting.append(field);
		if (i < keys_size - 1)
		{
			field_setting.append(", ");
		}
	}

	QString sql_query = QString("UPDATE `%1` SET %2 WHERE `%3` = \"%4\"")
					.arg(m_table_name)
					.arg(field_setting)
					.arg(m_primary_key_field_name)
					.arg(m_fields[m_primary_key_field_name].first.toString());

	QSqlQuery query;
	query.exec("BEGIN TRANSACTION");
	bool query_succeed = query.exec(sql_query);
	if (query_succeed)
	{
		query.exec("COMMIT TRANSACTION");
		m_removed = false;
		m_concretized = true;
	}
	else
	{
		query.exec("ROLLBACK TRANSACTION");
		m_last_error = query.lastError().text();
	}
	query.exec("END TRANSACTION");
	return query_succeed;
}


bool SQLiteORM::create()
{
	QString fields_name;
	QString fields_values;
	QList<QString> keys = m_fields.keys();
	int keys_size = keys.size();
	for (int i = 0; i < keys_size; i++)
	{
		if (keys[i] != m_primary_key_field_name)
		{
			QString field_name = QString("`%1`")
								 .arg(keys[i]);
			QString field_value = QString("\"%1\"")
								  .arg(m_fields[keys[i]].first.toString());

			fields_name.append(field_name);
			fields_values.append(field_value);

			if (i < keys_size - 1)
			{
				fields_name.append(", ");
				fields_values.append(", ");
			}
		}
	}

	QString sql_query = QString("INSERT INTO `%1` (%2) VALUES (%3)")
						.arg(m_table_name)
						.arg(fields_name)
						.arg(fields_values);
	QString sql_query_lock = QString("LOCK TABLE %1")
							 .arg(m_table_name);
	QString sql_query_unlock = QString("UNLOCK TABLE");


	QSqlQuery query;
	query.exec("BEGIN TRANSACTION");
	bool query_succeed = query.exec(sql_query);
	if (query_succeed)
	{
		query.exec("COMMIT TRANSACTION");
		query.exec("SELECT last_insert_rowid()");
		query.first();
		m_fields[m_primary_key_field_name].first = query.value(0);
		m_removed = false;
		m_concretized = true;
	}
	else
	{
		query.exec("ROLLBACK TRANSACTION");
		m_last_error = query.lastError().text();
	}
	query.exec("END TRANSACTION");
	return query_succeed;
}
