#include "../core/section.h"
#include "sectionsetanimationevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {

	/**
	 * Constructor. Changes to the specified animation.
	 * @param time Time to run the Event.
	 * @param section Section to update.
	 * @param animation Animation to display.
	 */
	SectionSetAnimationEvent::SectionSetAnimationEvent(unsigned long time, Section* section, Animation* animation, bool preserve_cycle_index) : Event(time) {
		this->section_ = section;
		this->animation_ = animation;
		this->preserve_cycle_index_ = preserve_cycle_index;
	}

	/**
	 * Constructor. Iterates through a collection of animations on each run	.
	 * @param time Time to run the Event.
	 * @param section Section to update.
	 * @param animations Collection of animations to iterate through.
	 * @param num_animations Number of animations to iterate through.
	 */
	SectionSetAnimationEvent::SectionSetAnimationEvent(unsigned long time, Section* section, Animation** animations, unsigned int num_animations, bool preserve_cycle_index) : Event(time) {
		this->section_ = section;
		this->animations_ = animations;
		this->num_animations_ = num_animations;
		this->preserve_cycle_index_ = preserve_cycle_index;
	}

	void SectionSetAnimationEvent::run() {
		// If we have a collection of animations, iterate through them.
		if(animations_) {
			// If necessary, transfer cycle_index over to the next animation.
			if (preserve_cycle_index_ && section_->get_animation()) {
				animations_[current_animation_]->set_cycle_index(section_->get_animation()->get_cycle_index());
			}

			section_->set_animation(animations_[current_animation_]);
			current_animation_++;

			// If we've reached the end of the list, reset the animation index.
			if (current_animation_ >= num_animations_) {
				current_animation_ = 0;
			}
		}
		else {	// Only run one animation.
			section_->set_animation(animation_);
		}
	}
}
