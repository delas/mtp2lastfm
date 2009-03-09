#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
	QDialog(parent),
	m_ui(new Ui::PreferencesDialog)
{
	m_ui->setupUi(this);
	m_ui->lineUsername->setText(DBConfig::get("LASTFM_USERNAME").value());

	if (DBConfig::get("PROXY_USAGE").value() == "true")
	{
		m_ui->proxyBox->setChecked(true);
	}
	m_ui->lineProxyHost->setText(DBConfig::get("PROXY_HOST").value());
	m_ui->lineProxyPort->setText(DBConfig::get("PROXY_PORT").value());
	m_ui->lineProxyUsername->setText(DBConfig::get("PROXY_USERNAME").value());
	m_ui->lineProxyPassword->setText(DBConfig::get("PROXY_PASSWORD").value());
}

PreferencesDialog::~PreferencesDialog()
{
	delete m_ui;
}

void PreferencesDialog::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}


void PreferencesDialog::on_buttonBox_accepted()
{
	if (DBConfig::get("LASTFM_USERNAME").value() != m_ui->lineUsername->text())
	{
		DBConfig::get("LASTFM_USERNAME").value(m_ui->lineUsername->text());
		DBConfig::get("LASTFM_PASSHASH").value(MD5String((char*)m_ui->lineUsername->text().toStdString().c_str()));
	}

	if (m_ui->proxyBox->isChecked())
	{
		DBConfig::get("PROXY_USAGE").value("true");
	}
	else
	{
		DBConfig::get("PROXY_USAGE").value("false");
	}
	DBConfig::get("PROXY_HOST").value(m_ui->lineProxyHost->text());
	DBConfig::get("PROXY_PORT").value(m_ui->lineProxyPort->text());
	DBConfig::get("PROXY_USERNAME").value(m_ui->lineProxyUsername->text());
	DBConfig::get("PROXY_PASSWORD").value(m_ui->lineProxyPassword->text());

	close();
}


void PreferencesDialog::on_buttonBox_rejected()
{
	close();
}
