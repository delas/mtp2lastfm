#ifndef QINTITEM_H
#define QINTITEM_H

#include <QStandardItem>

/**
 * This class is used to display an integer value in an QStandardItemModel
 *
 * @author Andrea Burattin
 */
class QIntItem : public QStandardItem
{
	public:
	/**
	 * One element constructor
	 *
	 * @param value the field value
	 */
	QIntItem(int value);

	virtual int type() const;

	virtual bool operator<(const QStandardItem& other) const;
};

#endif // QINTITEM_H
