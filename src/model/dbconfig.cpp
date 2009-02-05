#include "dbconfig.h"

DBConfig::DBConfig()
		: SQLiteORM()
{
	buildStructure();
}


DBConfig DBConfig::get(const QString& name)
{
	DBConfig dbc;
	QString where_condition = QString("`name` = \"%1\"")
							  .arg(name);
	QList<SQLiteORM> configs = dbc.getAll(where_condition, "");

	if (configs.size() == 0)
	{
		/* there isn't this config yet */
		dbc.setFieldValue("name", name);
	}
	else
	{
		/* config found */
		dbc.assignValue(configs[0]);
	}
	return dbc;
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
//	buildStructure();
	setFieldValue("value", value);
	save();
}
