#include "showcontroller.h"

ShowController::ShowController(MaestroController* maestro_controller) {
	this->maestro_controller_ = maestro_controller;

	if (maestro_controller_->get_show() == nullptr) {
		this->show_ = maestro_controller_->get_maestro()->set_show(nullptr, 0);
	}
	else {
		this->show_ = maestro_controller_->get_maestro()->get_show();
	}
}

Event* ShowController::add_event(uint16_t time, uint8_t *cue) {
	if (cue != nullptr) {
		events_.push_back(Event(time, cue));
		initialize_events();

		return &events_[events_.size() - 1];
	}

	return nullptr;
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
	initialize_events();
}
