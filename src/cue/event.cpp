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
		set_time(time);
		set_cue(cue);
	}

	/**
	 * Copy constructor.
	 * Added to support storing Events in a vector in PixelMaestro Studio.
	 * @param other Event to copy.
	 */
	Event::Event(const Event& other) {
		set_cue(other.cue_);
		this->time_ = other.time_;
	}

	/**
	 * Copy assignment operator.
	 * Added to support storing Events in a vector in PixelMaestro Studio.
	 * @param other Event to copy.
	 * @return New Event.
	 */
	Event& Event::operator=(const Event& other) {
		set_cue(other.cue_);
		this->time_ = other.time_;
		return *this;
	}

	/**
	 * Returns the Event's Cue.
	 * The Show passes this to the CueController when the Event runs.
	 * @return Cue.
	 */
	uint8_t* Event::get_cue() const {
		return cue_;
	}

	/**
	 * Returns the time that this Event will run.
	 * @return Event's start time.
	 */
	uint32_t Event::get_time() const {
		return time_;
	}

	bool Event::operator ==(const Event& other) {
		bool match = false;

		if (other.get_time() == this->time_) {
			uint32_t size = IntByteConvert::byte_to_uint32(&other.get_cue()[(uint8_t)CueController::Byte::SizeByte1]);
			for (uint32_t i = 0; i < size; i++) {
				if (other.get_cue()[i] != cue_[i]) {
					return match;
				}
			}

			match = true;
		}

		return match;
	}

	/**
	 * Sets the Event's Cue.
	 * @param cue Cue to run when the Event is triggered.
	 */
	void Event::set_cue(uint8_t* cue) {
		delete [] this->cue_;

		uint32_t size = IntByteConvert::byte_to_uint32(&cue[(uint8_t)CueController::Byte::SizeByte1]);
		this->cue_ = new uint8_t[size];
		for (uint32_t i = 0; i < size; i++) {
			this->cue_[i] = cue[i];
		}
	}

	/**
	 * Sets the Event's start time.
	 * @param time Time that the Event is triggered.
	 */
	void Event::set_time(uint32_t time) {
		this->time_ = time;
	}

	Event::~Event() {
		delete[] cue_;
	}
}
