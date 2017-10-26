#include "cue/cuecontroller.h"
#include "showcontrol.h"
#include "ui_showcontrol.h"

ShowControl::ShowControl(ShowController* show_controller, CueController* cue_controller, QWidget *parent) : QDialog(parent), ui(new Ui::ShowControl) {
	this->show_controller_ = show_controller;
	this->cue_controller_ = cue_controller;
	ui->setupUi(this);

	ui->lastActionLineEdit->setText(QString::fromStdString(cue_interpreter_.interpret_cue(cue_controller->get_cue())));
	refresh_event_list();
}

/// Adds the current action as a new Event
void ShowControl::on_addEventPushButton_clicked() {
	Event* event = show_controller_->add_event(ui->timeSpinBox->value(), cue_controller_->get_cue());

	// Add the Event to the list
	QString text = QString::number(event->get_time()) + QString(": ") + QString::fromStdString(cue_interpreter_.interpret_cue(cue_controller_->get_cue()));
	ui->eventListWidget->addItem(text);
}

/// Redraws the Event list.
void ShowControl::refresh_event_list() {
	// Temporary var for Events.
	Event* event;

	// TODO: Crash when reopening dialog
	for (uint8_t i = 0; i < show_controller_->get_num_events(); i++) {
		event = &show_controller_->get_events()[i];
		QString text = QString::number(event->get_time()) + QString(": ") + QString::fromStdString(cue_interpreter_.interpret_cue(event->get_cue()));
		ui->eventListWidget->addItem(text);
	}
}

ShowControl::~ShowControl() {
	delete ui;
}
