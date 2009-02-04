#ifndef CONFIGURATIONLOADING_H
#define CONFIGURATIONLOADING_H

#include <QtGui/QDialog>
#include <QDesktopWidget>
#include "../config.h"

namespace Ui
{
	class ConfigurationLoading;
}
class LoaderThread;

class ConfigurationLoading : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(ConfigurationLoading)

	public:
	explicit ConfigurationLoading(LoaderThread* loader, QWidget *parent = 0);
	virtual ~ConfigurationLoading();

	public slots:
	/**
	 * This slot can update informations
	 *
	 * @param action a string to describe the in progress action
	 * @param steps new, percentual, of completed job
	 */
	void updateProgress(const QString& action, int steps);

	protected:
	virtual void changeEvent(QEvent *e);

	private:
	Ui::ConfigurationLoading *m_ui;
	LoaderThread* m_loader;
};

#endif // CONFIGURATIONLOADING_H
