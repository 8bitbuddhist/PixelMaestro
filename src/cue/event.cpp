/*
 *
 * Event.cpp - Base class for Show events.
 */
#include "../cue/cue.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	/**
	 * Constructor.
	 * @param time Event's start time.
	 * @param Maestro The Maestro that the Cue will run on.
	 * @param Cue The Cue to run. This will be copied over to the Event.
	 * @param size The size of the Cue.
	 */
	Event::Event(unsigned long time, Maestro* maestro, const unsigned char* cue) {
		this->maestro_ = maestro;
		this->time_ = time;

		unsigned char size = cue[Cue::Bit::SizeBit] + Cue::Bit::PayloadBit;
		cue_ = new unsigned char[size];
		for (unsigned char i = 0; i < size; i++) {
			cue_[i] = cue[i];
		}
	}

	/**
	 * Returns the time that this Event will run.
	 * @return Event's start time.
	 */
	unsigned long Event::get_time() {
		return this->time_;
	}

	void Event::run() {
		Cue::run(maestro_, cue_);
	}

	Event::~Event() {
		delete[] cue_;
	}
}
