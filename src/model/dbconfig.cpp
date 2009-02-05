#include "dbconfig.h"

DBConfig::DBConfig()
		: SQLiteORM()
{
}


DBConfig DBConfig::get(const QString& name)
{
	QString where_condition = QString("`name` = \"%1\"").arg(name);
	QList<DBConfig> configs getAll(where_condition);

	if (configs.size() == 0)
	{
		/* there isn't this config yet */
		DBConfig dbc;
		dbc.setFieldValue("name", name);
		dbc.save();
		return dbc;
	}
	else
	{
		/* config found */
		return configs[0];
	}
}


void DBConfig::buildStructure()
{
	setTableName("config");

	addModelDescriptor("id", NUMERIC);
	addModelDescriptor("name", TEXT);
	addModelDescriptor("value", TEXT);

	setPrimaryKeyFieldName("id");
}


QString DBConfig::value()
{
	return getField("value").toString();
}


void DBConfig::value(const QString& value)
{
	setFieldValue("value", value);
}
