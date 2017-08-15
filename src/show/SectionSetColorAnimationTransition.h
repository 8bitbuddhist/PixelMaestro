#ifndef SECTIONSETCOLORANIMATIONTRANSITION_H
#define SECTIONSETCOLORANIMATIONTRANSITION_H

#include "../Section.h"
#include "Transition.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionSetColorAnimationTransition : public Transition {
		public:
			SectionSetColorAnimationTransition(unsigned long time, Section *section, Section::ColorAnimations animation_, bool reverseAnimation, Section::AnimationOrientations orientation);
			SectionSetColorAnimationTransition(unsigned long time, Section *section, Section::ColorAnimations *animations, unsigned int numAnimations, bool reverseAnimation, Section::AnimationOrientations orientation);
			void run();

		private:
			Section::ColorAnimations animation_;;
			Section::ColorAnimations *animations_ = nullptr;
			unsigned int num_animations_;
			Section::AnimationOrientations orientation;
			bool reverseAnimation;
			Section *section_;

	};
}

#endif // SECTIONSETCOLORANIMATIONTRANSITION_H
