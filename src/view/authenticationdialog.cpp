#include "authenticationdialog.h"
#include "ui_authenticationdialog.h"

AuthenticationDialog::AuthenticationDialog(QWidget *parent)
	: QDialog(parent), m_ui(new Ui::AuthenticationDialog)
{
	m_ui->setupUi(this);
	m_ui->lineUsername->setText(DBConfig::get("LASTFM_USERNAME").value());
}


AuthenticationDialog::~AuthenticationDialog()
{
	delete m_ui;
}


void AuthenticationDialog::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}


void AuthenticationDialog::on_buttonBox_accepted()
{
	DBConfig::get("LASTFM_USERNAME").value(m_ui->lineUsername->text());
	DBConfig::get("LASTFM_PASSHASH").value(MD5String((char*)m_ui->lineUsername->text().toStdString().c_str()));
	close();
}


void AuthenticationDialog::on_buttonBox_rejected()
{
	close();
}
