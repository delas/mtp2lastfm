#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
	QDialog(parent),
	m_ui(new Ui::PreferencesDialog)
{
	m_ui->setupUi(this);
	m_ui->lineUsername->setText(DBConfig::get("SCROBBLER_USERNAME").value());
	QString temp_uri = DBConfig::get("SCROBBLER_URI").value();
	if (temp_uri == LASTFM_HANDSHAKE)
	{
		m_ui->radioServerLast->setChecked(true);
		m_ui->radioServerLibre->setChecked(false);
	}
	else
	{
		m_ui->radioServerLast->setChecked(false);
		m_ui->radioServerLibre->setChecked(true);
	}

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
	if (DBConfig::get("SCROBBLER_USERNAME").value() != m_ui->lineUsername->text())
	{
		DBConfig::get("SCROBBLER_USERNAME").value(m_ui->lineUsername->text());
		DBConfig::get("SCROBBLER_PASSHASH").value(MD5String((char*)m_ui->lineUsername->text().toStdString().c_str()));
	}
	QString temp_uri = LIBREFM_HANDSHAKE;
	if (m_ui->radioServerLast->isChecked())
	{
		temp_uri = LASTFM_HANDSHAKE;
	}
	DBConfig::get("SCROBBLER_URI").value(temp_uri);

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
