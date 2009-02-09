#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H

#include <QtGui/QDialog>
#include "../model/dbconfig.h"
#include "../model/md5.h"

namespace Ui
{
	class AuthenticationDialog;
}

class AuthenticationDialog : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(AuthenticationDialog)

	public:
	explicit AuthenticationDialog(QWidget *parent = 0);
	virtual ~AuthenticationDialog();

	protected:
	virtual void changeEvent(QEvent *e);

	public slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

	private:
	Ui::AuthenticationDialog *m_ui;
};

#endif // AUTHENTICATIONDIALOG_H
