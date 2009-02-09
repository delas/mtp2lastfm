#include "qintitem.h"

QIntItem::QIntItem(int value)
		: QStandardItem(QString("%1").arg(value))
{
}


int QIntItem::type() const
{
	return 1001;
}


bool QIntItem::operator< (const QStandardItem& other) const
{
	return (data().toInt() < other.data().toInt());
}
