#include "controller/cueinterpreter.h"
#include "showcontroller.h"

ShowController::ShowController(MaestroController* maestro_controller) {
	this->maestro_controller_ = maestro_controller;

	if (maestro_controller_->get_show() == nullptr) {
		this->show_ = maestro_controller_->get_maestro()->set_show(nullptr, 0);
	}
	else {
		this->show_ = maestro_controller_->get_maestro()->get_show();
	}

	events_.clear();
	event_descriptions_.clear();
}

Event* ShowController::add_event(uint16_t time, uint8_t *cue) {
	if (cue != nullptr) {
		events_.push_back(Event(time, cue));

		QString description = QString::number(time);
		description.append(QString(": "));
		description.append(QString::fromStdString(cue_interpreter_.interpret_cue(cue)));

		event_descriptions_.push_back(description);
		initialize_events();

		return &events_[events_.size() - 1];
	}

	return nullptr;
}

Event* ShowController::get_event(uint16_t index) {
	return &events_.at(index);
}

QString ShowController::get_event_description(uint16_t index) {
	return event_descriptions_.at(index);
}

std::vector<Event> ShowController::get_events() {
	return events_;
}

uint8_t ShowController::get_num_events() {
	return events_.size();
}

void ShowController::initialize_events() {
	show_->set_events(&events_[0], events_.size());
}

void ShowController::remove_event(uint16_t index) {
	events_.erase(events_.begin() + index);
	event_descriptions_.erase(event_descriptions_.begin() + index);
	initialize_events();
}
