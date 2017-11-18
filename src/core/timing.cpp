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
	uint16_t Timing::get_interval() {
		return interval_;
	}

	/**
	 * Returns the last update time.
	 * @return Last update time.
	 */
	uint32_t Timing::get_last_time() {
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

	// AnimationTiming Methods
	/**
	 * Constructor. Sets the speed and pause intervals.
	 * @param interval Amount of time (in milliseconds) between animation cycles.
	 * @param pause Delay (in milliseconds) before starting the next animation cycle.
	 */
	AnimationTiming::AnimationTiming(uint16_t interval, uint16_t pause) {
		set_interval(interval, pause);
	}

	/**
	 * Returns the amount of time (in milliseconds) to wait before starting an animation cycle.
	 * @return Pause interval.
	 */
	uint16_t AnimationTiming::get_pause() {
		return pause_;
	}

	/**
	 * Returns the number of steps in the current cycle.
	 * @return Cycle steps.
	 */
	uint8_t AnimationTiming::get_step_count() {
		return step_count_;
	}

	/**
	 * Recalculates the number of steps in the Animation.
	 * @param fade Whether the Animation is fading.
	 * @param refresh_interval The Maestro's refresh interval.
	 */
	void AnimationTiming::recalculate_step_count(bool fade, uint16_t refresh_interval) {
		/*
		 * If fading, calculate the distance in steps between the current cycle and the next cycle.
		 * Otherwise, just jump to the next cycle.
		 */
		if (fade) {
			step_count_ = (interval_ - pause_) / (float)refresh_interval;

			// Make sure step_count_ is at least 1
			if (step_count_ == 0) {
				step_count_ = 1;
			}
		}
		else {
			step_count_ = 1;
		}
	}

	/**
	 * Sets the amount of time between events.
	 *
	 * @param interval Amount of time (in milliseconds) between events.
	 * @param pause The amount of time (in milliseconds) to wait before starting an animation cycle.
	 */
	void AnimationTiming::set_interval(uint16_t interval, uint16_t pause) {
		this->interval_ = interval;
		this->pause_ = pause;
	}
}
