#include "tracksimport.h"
#include "ui_tracksimport.h"
#include "../threads/tracksimporter.h"

TracksImport::TracksImport(TracksImporter* importer, QWidget *parent) :
	QDialog(parent), m_ui(new Ui::TracksImport)
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

	m_importer = importer;
	connect(m_importer, SIGNAL(updateProgress(const QString&, int)),
			this, SLOT(updateProgress(const QString&, int)));
	connect(m_importer, SIGNAL(errorCatched(const QString&)),
			this, SLOT(errorCatched(const QString&)));
}


TracksImport::~TracksImport()
{
	delete m_ui;
}


void TracksImport::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}


void TracksImport::updateProgress(const QString& action, int steps)
{
	m_ui->label->setText(action);
	m_ui->progressBar->setValue(steps);
	if (steps == 100)
	{
		m_ui->buttonBox->setEnabled(true);
	}
}


void TracksImport::errorCatched(const QString& error)
{
	m_ui->label->setText(error);
	m_ui->progressBar->setValue(100);
	m_ui->buttonBox->setEnabled(true);
}


void TracksImport::on_buttonBox_accepted()
{
	accept();
}
