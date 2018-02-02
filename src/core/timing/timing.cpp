/*
 * Timing - Classes for managing time-sensitive actions.
 */

#include "timing.h"

namespace PixelMaestro {
	/**
	 * Constructor. Sets the speed interval.
	 * @param interval Amount of time (in milliseconds) between events.
	 */
	Timing::Timing(uint16_t interval) {
		set_interval(interval);
	}

	/**
	 * Returns the interval between events.
	 * @return Interval.
	 */
	uint16_t Timing::get_interval() const {
		return interval_;
	}

	/**
	 * Returns the last update time.
	 * @return Last update time.
	 */
	uint32_t Timing::get_last_time() const {
		return last_time_;
	}

	/**
	 * Sets the amount of time between events.
	 *
	 * @param interval Amount of time (in milliseconds) between events.
	 */
	void Timing::set_interval(uint16_t interval) {
		this->interval_ = interval;
	}

	/**
	 * Sets the last time the timer ran.
	 * @param last_time Time (in milliseconds) that the timer last ran.
	 */
	void Timing::set_last_time(uint32_t last_time) {
		this->last_time_ = last_time;
	}

	/**
	 * Checks timings.
	 * @param current_time Current program runtime.
	 * @return If the runtime exceeds the interval, return true.
	 */
	bool Timing::update(const uint32_t& current_time) {
		if ((current_time - last_time_) >= interval_) {
			last_time_ = current_time;
			return true;
		}

		return false;
	}
}
