#include "newversiondialog.h"
#include "ui_newversiondialog.h"

NewVersionDialog::NewVersionDialog(const QString& version,
								   const QString& date,
								   const QString& note,
								   const QString& url,
								   QWidget *parent) :
	QDialog(parent),
	m_ui(new Ui::NewVersionDialog)
{
	m_ui->setupUi(this);

	/* center the application */
	setGeometry(
			QApplication::desktop()->width()/2 - width()/2,
			QApplication::desktop()->height()/2 - height()/2,
			width(),
			height());

	QString title = tr("New version %1 (%2) available").arg(version).arg(date);
	m_ui->groupBox->setTitle(title);
	m_ui->label->setText(note);
	m_ui->label_url->setText(url);
}


NewVersionDialog::~NewVersionDialog()
{
	delete m_ui;
}


void NewVersionDialog::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}


void NewVersionDialog::on_buttonBox_accepted()
{
	accept();
}
