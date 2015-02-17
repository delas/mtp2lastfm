#ifndef TRACKSIMPORT_H
#define TRACKSIMPORT_H

#include <QtGui/QDialog>
#include <QDesktopWidget>

namespace Ui
{
	class TracksImport;
}
class TracksImporter;

class TracksImport : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(TracksImport)

	public:
	explicit TracksImport(TracksImporter* importer, QWidget *parent = 0);
	virtual ~TracksImport();

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
	Ui::TracksImport *m_ui;
	TracksImporter* m_importer;
};

#endif // TRACKSIMPORT_H
