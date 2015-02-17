#ifndef SCROBBLERPROGRESS_H
#define SCROBBLERPROGRESS_H

#include <QtGui/QDialog>
#include <QDesktopWidget>

namespace Ui
{
	class ScrobblerProgress;
}
class Scrobbler;

class ScrobblerProgress : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(ScrobblerProgress)

	public:
	explicit ScrobblerProgress(Scrobbler* scrobbler, QWidget *parent = 0);
	virtual ~ScrobblerProgress();

	public slots:
	/**
	 * This slot can update informations
	 *
	 * @param action a string to describe the in progress action
	 * @param steps new, percentual, of completed job
	 */
	void updateProgress(const QString& action, int steps);

	/**
	 * This slot catch an error
	 *
	 * @param error the error description
	 */
	void errorCatched(const QString& error);

	protected slots:
	void on_buttonBox_accepted();
	inline void reject() {}

	protected:
	virtual void changeEvent(QEvent *e);

	private:
	Ui::ScrobblerProgress *m_ui;
	Scrobbler* m_scrobbler;
};

#endif // SCROBBLERPROGRESS_H
