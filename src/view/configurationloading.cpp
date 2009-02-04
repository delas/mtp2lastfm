#include "configurationloading.h"
#include "../threads/loaderthread.h"
#include "ui_configurationloading.h"

ConfigurationLoading::ConfigurationLoading(LoaderThread* loader,
										   QWidget *parent)
	: QDialog(parent), m_ui(new Ui::ConfigurationLoading)
{
	m_ui->setupUi(this);
	setWindowTitle(windowTitle().append(" ").append(CLIENT_VERSION));

	/* center the application */
	setGeometry(
			QApplication::desktop()->width()/2 - width()/2,
			QApplication::desktop()->height()/2 - height()/2,
			width(),
			height());

	m_ui->progressBar->setValue(0);
	m_ui->label->setText("Loading configuration...");

	m_loader = loader;
	connect(m_loader, SIGNAL(updateProgress(const QString&, int)),
		this, SLOT(updateProgress(const QString&, int)));
}


ConfigurationLoading::~ConfigurationLoading()
{
	delete m_ui;
}


void ConfigurationLoading::updateProgress(const QString& action, int steps)
{
	m_ui->label->setText(action);
	m_ui->progressBar->setValue(steps);
}


void ConfigurationLoading::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
