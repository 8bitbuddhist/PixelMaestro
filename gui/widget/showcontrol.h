#ifndef SHOWCONTROL_H
#define SHOWCONTROL_H

#include <QDialog>
#include "controller/cueinterpreter.h"
#include "controller/showcontroller.h"

namespace Ui {
	class ShowControl;
}

class ShowControl : public QDialog {
		Q_OBJECT

	public:
		explicit ShowControl(ShowController* show_controller, CueController* cue_controller, QWidget *parent = 0);
		~ShowControl();
		void refresh_event_list();

	private slots:
		void on_addEventPushButton_clicked();

	private:
		CueController* cue_controller_ = nullptr;
		CueInterpreter cue_interpreter_;
		ShowController* show_controller_ = nullptr;
		Ui::ShowControl *ui;
};

#endif // SHOWCONTROL_H
