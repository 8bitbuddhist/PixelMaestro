/*
 * Event.cpp - Base class for Show events.
 */
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	/**
	 * Constructor.
	 * @param time Event's start time.
	 */
	Event::Event(unsigned long time) {
		this->time_ = time;
	}

	/**
	 * Returns the time that this Event will run.
	 * @return Event's start time.
	 */
	unsigned long Event::get_time() {
		return this->time_;
	}

	/**
	 * Sets the time that this event will run.
	 * @param time Event's start time.
	 */
	void Event::set_time(unsigned long time) {
		this->time_ = time;
	}
}
