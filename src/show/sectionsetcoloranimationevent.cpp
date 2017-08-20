#include "../section.h"
#include "sectionsetcoloranimationevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {

	/**
	 * Constructor. Changes to the specified animation.
	 * @param time Time to run the Event.
	 * @param section Section to update.
	 * @param animation Animation to display.
	 * @param reverseAnimation Whether to reverse the animation.
	 * @param orientation Animation orientation.
	 */
	SectionSetColorAnimationEvent::SectionSetColorAnimationEvent(unsigned long time, Section *section, Section::ColorAnimations animation, bool reverseAnimation, Section::AnimationOrientations orientation) : Event(time) {
		this->section_ = section;
		this->animation_ = animation;
		this->reverseAnimation = reverseAnimation;
		this->orientation = orientation;
	}

	/**
	 * Constructor. Automatically scrolls through a collection of animations.
	 * @param time Time to run the Event.
	 * @param section Section to update.
	 * @param animations Collection of animations to scroll through.
	 * @param numAnimations Number of animations to scroll through.
	 * @param reverseAnimation Whether to reverse the animation.
	 * @param orientation Animation orientation.
	 */
	SectionSetColorAnimationEvent::SectionSetColorAnimationEvent(unsigned long time, Section *section, Section::ColorAnimations *animations, unsigned int numAnimations, bool reverseAnimation, Section::AnimationOrientations orientation) : Event(time) {
		this->section_ = section;
		this->animations_ = animations;
		this->num_animations_ = numAnimations;
		this->reverseAnimation = reverseAnimation;
		this->orientation = orientation;
	}

	void SectionSetColorAnimationEvent::run() {
		// If we have a collection of animations, iterate through them, otherwise jump straight to the specified animation
		if(this->animations_) {
			this->section_->setColorAnimation(Section::ColorAnimations::NEXT, this->reverseAnimation, this->orientation);
			bool isEnabled = false;
			for (unsigned int animation = 0; animation < this->num_animations_; animation++) {
				if(this->animations_[animation] == this->section_->getColorAnimation()) {
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
			this->section_->setColorAnimation(this->animation_, this->reverseAnimation, this->orientation);
		}
	}
}
