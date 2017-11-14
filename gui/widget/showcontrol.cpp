#include <QListWidget>
#include <QMessageBox>
#include "cue/cuecontroller.h"
#include "showcontrol.h"
#include "ui_showcontrol.h"

ShowControl::ShowControl(ShowController* show_controller, CueController* cue_controller, QWidget *parent) : QDialog(parent), ui(new Ui::ShowControl) {
	this->show_controller_ = show_controller;
	this->cue_controller_ = cue_controller;
	ui->setupUi(this);

	// Initialize timer and update it kinda frequently-ish
	timer_.setTimerType(Qt::CoarseTimer);
	connect(&timer_, SIGNAL(timeout()), this, SLOT(refresh_maestro_last_time()));
	timer_.start(250);

	ui->lastActionLineEdit->setText(QString::fromStdString(cue_interpreter_.interpret_cue(cue_controller->get_cue())));
	refresh_event_list();
}

/// Adds the current action as a new Event
void ShowControl::on_addEventPushButton_clicked() {
	// Verify that the Cue isn't already in the list
	Event* test_event;
	for (uint8_t i = 0; i < show_controller_->get_num_events(); i++) {
		test_event = show_controller_->get_event(i);
		if (test_event->get_time() == (uint8_t)ui->timeSpinBox->value() &&
			QString::fromLocal8Bit((const char*)test_event->get_cue()).contains(QString::fromLocal8Bit((const char*)cue_controller_->get_cue()))) {
			QMessageBox::warning(nullptr, "Unable to Add Event", "This Event has already been added.");
			return;
		}
	}

	show_controller_->add_event(ui->timeSpinBox->value(), cue_controller_->get_cue());
	new QListWidgetItem(show_controller_->get_event_description(show_controller_->get_num_events() - 1), ui->eventListWidget);
}

/// Redraws the Event list.
void ShowControl::refresh_event_list() {
	for (uint8_t i = 0; i < show_controller_->get_num_events(); i++) {
		new QListWidgetItem(show_controller_->get_event_description(i), ui->eventListWidget);
	}
}

/**
 * Displays the Maestro's last run time.
 */
void ShowControl::refresh_maestro_last_time() {
	ui->runtimeLineEdit->setText(QString::number(cue_controller_->get_maestro()->get_last_refresh()));
}

ShowControl::~ShowControl() {
	delete ui;
}
