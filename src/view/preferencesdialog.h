#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QtGui/QDialog>
#include "../model/dbconfig.h"
#include "../model/md5.h"
#include "../config.h"

namespace Ui
{
	class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(PreferencesDialog)

	public:
	explicit PreferencesDialog(QWidget *parent = 0);
	virtual ~PreferencesDialog();

	protected:
	virtual void changeEvent(QEvent *e);

	public slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

	private:
	Ui::PreferencesDialog *m_ui;
};

#endif // PREFERENCESDIALOG_H
