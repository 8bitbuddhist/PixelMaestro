#ifndef SHOWCONTROL_H
#define SHOWCONTROL_H

#include <QDialog>
#include <QTimer>
#include "controller/cueinterpreter.h"
#include "controller/showcontroller.h"

namespace Ui {
	class ShowControl;
}

class ShowController;

class ShowControl : public QDialog {
		Q_OBJECT

	public:
		explicit ShowControl(ShowController* show_controller, CueController* cue_controller, QWidget *parent = 0);
		~ShowControl();
		void refresh_event_list();

	private slots:
		void on_addEventPushButton_clicked();
		void refresh_maestro_last_time();

	private:
		CueController* cue_controller_ = nullptr;
		CueInterpreter cue_interpreter_;

		/// Updates the current Maestro time.
		QTimer timer_;

		ShowController* show_controller_ = nullptr;
		Ui::ShowControl *ui;
};

#endif // SHOWCONTROL_H
