#include "scrobblerprogress.h"
#include "ui_scrobblerprogress.h"
#include "../threads/scrobbler.h"

ScrobblerProgress::ScrobblerProgress(Scrobbler* scrobbler, QWidget *parent) :
	QDialog(parent), m_ui(new Ui::ScrobblerProgress)
{
	m_ui->setupUi(this);

	/* center the application */
	setGeometry(
			QApplication::desktop()->width()/2 - width()/2,
			QApplication::desktop()->height()/2 - height()/2,
			width(),
			height());

	m_ui->progressBar->setValue(0);
	m_ui->label->setText("");

	m_scrobbler = scrobbler;
	connect(m_scrobbler, SIGNAL(updateProgress(const QString&, int)),
			this, SLOT(updateProgress(const QString&, int)));
	connect(m_scrobbler, SIGNAL(errorCatched(const QString&)),
			this, SLOT(errorCatched(const QString&)));
}


ScrobblerProgress::~ScrobblerProgress()
{
	delete m_ui;
}


void ScrobblerProgress::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}


void ScrobblerProgress::updateProgress(const QString& action, int steps)
{
	m_ui->label->setText(action);
	m_ui->progressBar->setValue(steps);
	if (steps == 100)
	{
		m_ui->buttonBox->setEnabled(true);
	}
}


void ScrobblerProgress::errorCatched(const QString& error)
{
	QString correct_data = error;
	if (error.contains("FAILED"))
	{
		correct_data
				.append("\n")
				.append(tr("Are you sure about username and password?"));
	}
	m_ui->label->setText(correct_data);
	m_ui->progressBar->setValue(100);
	m_ui->buttonBox->setEnabled(true);
}


void ScrobblerProgress::on_buttonBox_accepted()
{
	close();
}
