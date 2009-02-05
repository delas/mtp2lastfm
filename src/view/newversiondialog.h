#ifndef NEWVERSIONDIALOG_H
#define NEWVERSIONDIALOG_H

#include <QtGui/QDialog>
#include <QDesktopWidget>

namespace Ui
{
	class NewVersionDialog;
}

class NewVersionDialog : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(NewVersionDialog)

	public:
	explicit NewVersionDialog(const QString& version,
							  const QString& date,
							  const QString& note,
							  const QString& url,
							  QWidget *parent = 0);
	virtual ~NewVersionDialog();

	protected:
	virtual void changeEvent(QEvent *e);

	protected slots:
	void on_buttonBox_accepted();

	private:
	Ui::NewVersionDialog *m_ui;
};

#endif // NEWVERSIONDIALOG_H
