#include "../section.h"
#include "sectionsetcoloranimationevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {

	/**
	 * Constructor. Changes to the specified animation.
	 * @param time Time to run the Event.
	 * @param section Section to update.
	 * @param animation Animation to display.
	 */
	SectionSetColorAnimationEvent::SectionSetColorAnimationEvent(unsigned long time, Section* section, ColorAnimation* animation) : Event(time) {
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
	SectionSetColorAnimationEvent::SectionSetColorAnimationEvent(unsigned long time, Section* section, ColorAnimation* animations, unsigned int num_animations) : Event(time) {
		this->section_ = section;
		this->animations_ = animations;
		this->num_animations_ = num_animations;
	}

	void SectionSetColorAnimationEvent::run() {
		// If we have a collection of animations, iterate through them, otherwise jump straight to the specified animation
		if(animations_) {
			section_->set_new_color_animation(animation_);
			bool isEnabled = false;
			for (unsigned int animation = 0; animation < num_animations_; animation++) {
				if(&animations_[animation] == section_->get_new_color_animation()) {
					isEnabled = true;
					break;
				}
			}

			// If this animation is disabled, try the next one
			if (!isEnabled) {
				this->run();
			}
		}
		else {
			section_->set_new_color_animation(animation_);
		}
	}
}
