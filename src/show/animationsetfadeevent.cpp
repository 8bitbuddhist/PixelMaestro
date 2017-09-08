#include "animationsetfadeevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	AnimationSetFadeEvent::AnimationSetFadeEvent(unsigned long time, Animation* animation, bool fade) : Event(time) {
		this->animation_ = animation;
		this->fade_ = fade;
	}

	void AnimationSetFadeEvent::run() {
		animation_->set_fade(fade_);
	}
}
