#include "animationsetfadeevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	/**
	 * Constructor. This Event toggles fading on an animation.
	 * @param time Time until the Event runs.
	 * @param animation Animation that the Event modifies.
	 * @param fade Whether or not to enable fading.
	 */
	AnimationSetFadeEvent::AnimationSetFadeEvent(unsigned long time, Animation* animation, bool fade) : Event(time) {
		this->animation_ = animation;
		this->fade_ = fade;
	}

	void AnimationSetFadeEvent::run() {
		animation_->set_fade(fade_);
	}
}
