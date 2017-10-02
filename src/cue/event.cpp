/*
 *
 * Event.cpp - Base class for Show events.
 */
#include "../cue/cuecontroller.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {

	/**
	 * Constructor. Loads the provided Cue into the CueController.
	 * @param time Event's start time.
	 * @param Maestro The Maestro that the Cue will run on.
	 * @param Cue The Cue to run. This will be copied to the Event, then loaded into the CueController.
	 * @param size The size of the Cue.
	 */
	Event::Event(uint32_t time, const uint8_t* cue) {
		this->time_ = time;

		uint8_t size = cue[CueController::Byte::SizeByte] + CueController::Byte::PayloadByte;
		cue_ = new uint8_t[size];
		for (uint8_t i = 0; i < size; i++) {
			cue_[i] = cue[i];
		}
	}

	/**
	 * Returns the time that this Event will run.
	 * @return Event's start time.
	 */
	uint32_t Event::get_time() {
		return this->time_;
	}

	void Event::run(CueController* controller) {
		controller->run(cue_);
	}

	Event::~Event() {
		delete[] cue_;
	}
}
