/*
 * AnimationTiming - Class for managing time-sensitive actions for Animations.
 */

#include "animationtiming.h"

namespace PixelMaestro {
	/**
	 * Constructor. Sets the speed and pause intervals.
	 * @param animation the Timing's parent Animation.
	 */
	AnimationTiming::AnimationTiming(Animation* animation) {
		this->animation_ = animation;
	}

	/**
	 * Returns the amount of time (in milliseconds) to wait before starting an animation cycle.
	 * @return Pause interval.
	 */
	uint16_t AnimationTiming::get_pause() const {
		return pause_;
	}

	/**
	 * Returns the number of steps in the current cycle.
	 * @return Cycle steps.
	 */
	uint8_t AnimationTiming::get_step_count() const {
		return step_count_;
	}

	/**
	 * Recalculates the number of steps in the Animation.
	 */
	void AnimationTiming::recalculate_step_count() {
		/*
		 * If fading, calculate the distance in steps between the current cycle and the next cycle.
		 * Otherwise, just jump to the next cycle.
		 */
		if (animation_->get_fade()) {
			step_count_ = (interval_ - pause_) / (float)animation_->get_section()->get_maestro()->get_timing()->get_interval();
		}
		else {
			step_count_ = 0;
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
		this->recalculate_step_count();
	}
}