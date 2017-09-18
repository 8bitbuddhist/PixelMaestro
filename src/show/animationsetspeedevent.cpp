#include "animationsetspeedevent.h"

namespace PixelMaestro {
	/**
	 * Constructor.
	 * Changes an Animation's speed. The speed is the amount of time between animation cycle changes.
	 * @param time Time until the Event runs.
	 * @param animation Animation to update.
	 * @param speed New speed.
	 * @param pause Pause interval.
	 */
	AnimationSetSpeedEvent::AnimationSetSpeedEvent(unsigned long time, Animation* animation, unsigned short speed, unsigned short pause) : Event(time) {
		this->animation_ = animation_;
		this->speed_ = speed;
		this->pause_ = pause;
	}

	void AnimationSetSpeedEvent::run() {
		animation_->set_speed(speed_, pause_);
	}
}
