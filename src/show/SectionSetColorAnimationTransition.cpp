#include "../Section.h"
#include "SectionSetColorAnimationTransition.h"

using namespace PixelMaestro;

namespace PixelMaestro {

	SectionSetColorAnimationTransition::SectionSetColorAnimationTransition(Section *section, unsigned long time, Section::ColorAnimations animation, bool reverseAnimation, Section::AnimationOrientations orientation) : Transition(time) {
		this->section_ = section;
		this->animation = animation;
		this->reverseAnimation = reverseAnimation;
		this->orientation = orientation;
	}

	void SectionSetColorAnimationTransition::run() {
		this->section_->setColorAnimation(this->animation, this->reverseAnimation, this->orientation);
	}
}
