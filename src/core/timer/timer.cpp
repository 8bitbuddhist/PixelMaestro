/*
 * Timer - Class for managing time-sensitive actions.
 */

#include "timer.h"

namespace PixelMaestro {
	/**
	 * Constructor. Sets the speed interval.
	 * @param interval Amount of time (in milliseconds) between events.
	 */
	Timer::Timer(uint16_t interval) {
		set_interval(interval);
	}

	/**
	 * Returns the interval between events.
	 * @return Interval.
	 */
	uint16_t Timer::get_interval() const {
		return interval_;
	}

	/**
	 * Returns the last update time.
	 * @return Last update time.
	 */
	uint32_t Timer::get_last_time() const {
		return last_time_;
	}

	/**
	 * Returns whether the Timer is currently running.
	 * @return true if running.
	 */
	bool Timer::get_running() const {
		return running_;
	}

	/**
	 * Sets the amount of time between events.
	 *
	 * @param interval Amount of time (in milliseconds) between events.
	 */
	void Timer::set_interval(uint16_t interval) {
		this->interval_ = interval;
	}

	/**
	 * Sets the last time the timer ran.
	 * @param last_time Time (in milliseconds) that the timer last ran.
	 */
	void Timer::set_last_time(uint32_t last_time) {
		this->last_time_ = last_time;
	}

	/// Starts the timer.
	void Timer::start() {
		running_ = true;
	}

	/// Stops the timer.
	void Timer::stop() {
		running_ = false;
	}

	/**
	 * Checks if the timer has gone off.
	 * @param current_time Current program runtime.
	 * @return If the runtime exceeds the interval, return true.
	 */
	bool Timer::update(const uint32_t& current_time) {
		if (running_ && ((current_time - last_time_) >= interval_)) {
			last_time_ = current_time;
			return true;
		}

		return false;
	}
}
