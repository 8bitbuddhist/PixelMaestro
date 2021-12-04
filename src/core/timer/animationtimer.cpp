/*
 * AnimationTimer - Class for managing time-sensitive actions for Animations.
 */

#include "animationtimer.h"
#include <math.h>

namespace PixelMaestro {
	/**
	 * Constructor.
	 * @param animation the timer's parent Animation.
	 */
	AnimationTimer::AnimationTimer(const Animation& animation) : animation_(animation) { }

	/**
	 * Returns the amount of time (in milliseconds) to wait before starting an animation cycle.
	 * @return Pause interval.
	 */
	uint16_t AnimationTimer::get_delay() const {
		return delay_;
	}

	/**
	 * Returns the number of steps in the current cycle.
	 * @return Cycle steps.
	 */
	uint8_t AnimationTimer::get_step_count() const {
		return step_count_;
	}

	/**
	 * Recalculates the number of steps in the Animation.
	 */
	void AnimationTimer::recalculate_step_count() {
		/*
		 * TODO: Thoughts on updating timing:
		 *	Right now, we time by frame (how long until the next frame) when we should probably time by cycle (how long to complete the animation).
		 *	The challenge is the interval is calculated around the frame.
		 *	To calculate around the cycle, we'd need the length of the cycle (e.g. # of colors in the palette).
		 */

		/*
		 * If fading, calculate the distance in steps between the current cycle and the next cycle.
		 * Otherwise, just jump to the next cycle.
		 */
		if (animation_.get_fade()) {
			step_count_ = fmax((interval_ - delay_) / (float)animation_.get_section().get_maestro().get_timer().get_interval(), 1);
		}
		else {
			step_count_ = 1;
		}
	}

	/**
	 * Sets the amount of time between events.
	 *
	 * @param interval Amount of time (in milliseconds) between events.
	 * @param delay The amount of time (in milliseconds) to wait before starting an animation cycle.
	 */
	void AnimationTimer::set_interval(uint16_t interval, uint16_t delay) {
		this->interval_ = interval;
		this->delay_ = delay;
		this->recalculate_step_count();
	}

	/**
	 * Checks if the timer has gone off.
	 * @param current_time Current program runtime.
	 * @return If the runtime exceeds the interval, return true.
	 */
	bool AnimationTimer::update(const uint32_t& current_time) {
		if (running_ && ((current_time - last_time_) >= (interval_))) {
			last_time_ = current_time;
			return true;
		}

		return false;
	}
}
