/*
 *
 * Event.cpp - Base class for Show events.
 */
#include "../cue/cuecontroller.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {

	/**
	 * Constructor. Copies the provided Cue into the Event.
	 * @param time Event's start time.
	 * @param Cue The Cue to run.
	 */
	Event::Event(uint32_t time, uint8_t* cue) {
		this->time_ = time;

		uint8_t size = cue[CueController::Byte::SizeByte] + CueController::Byte::PayloadByte;
		cue_ = new uint8_t[size];
		for (uint8_t i = 0; i < size; i++) {
			cue_[i] = cue[i];
		}
	}

	/**
	 * Returns the Event's Cue.
	 * The Show passes this to the CueController when the Event runs.
	 * @return Cue.
	 */
	uint8_t* Event::get_cue() {
		return cue_;
	}

	/**
	 * Returns the time that this Event will run.
	 * @return Event's start time.
	 */
	uint32_t Event::get_time() {
		return time_;
	}

	Event::~Event() {
		delete[] cue_;
	}
}
