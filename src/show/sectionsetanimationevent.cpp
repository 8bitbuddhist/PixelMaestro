#include "../section.h"
#include "sectionsetanimationevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {

	/**
	 * Constructor. Changes to the specified animation.
	 * @param time Time to run the Event.
	 * @param section Section to update.
	 * @param animation Animation to display.
	 */
	SectionSetAnimationEvent::SectionSetAnimationEvent(unsigned long time, Section* section, Animation* animation) : Event(time) {
		this->section_ = section;
		this->animation_ = animation;
	}

	/**
	 * Constructor. Automatically scrolls through a collection of animations.
	 * @param time Time to run the Event.
	 * @param section Section to update.
	 * @param animations Collection of animations to scroll through.
	 * @param num_animations Number of animations to scroll through.
	 */
	SectionSetAnimationEvent::SectionSetAnimationEvent(unsigned long time, Section* section, Animation* animations, unsigned int num_animations) : Event(time) {
		this->section_ = section;
		this->animation_ = animations;
		this->num_animations_ = num_animations;
	}

	void SectionSetAnimationEvent::run() {
		// If we have a collection of animations, iterate through them.
		if(num_animations_ > 0) {
			section_->set_color_animation(animation_);
			bool isEnabled = false;
			for (unsigned int index = 0; index < num_animations_; index++) {
				if(&animation_[index] == section_->get_color_animation()) {
					isEnabled = true;
					break;
				}
			}

			// If this animation is disabled, try the next one
			if (!isEnabled) {
				this->run();
			}
		}
		else {	// Only one animation set.
			section_->set_color_animation(animation_);
		}
	}
}
