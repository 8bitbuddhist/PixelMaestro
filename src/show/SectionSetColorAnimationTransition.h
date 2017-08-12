#ifndef SECTIONSETCOLORANIMATIONTRANSITION_H
#define SECTIONSETCOLORANIMATIONTRANSITION_H

#include "../Section.h"
#include "Transition.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionSetColorAnimationTransition : public Transition {
		public:
			SectionSetColorAnimationTransition(Section *section, unsigned long time, Section::ColorAnimations animation, bool reverseAnimation, Section::AnimationOrientations orientation);
			void run();

		private:
			Section::ColorAnimations animation;
			Section::AnimationOrientations orientation;
			bool reverseAnimation;
			Section *section_;

	};
}

#endif // SECTIONSETCOLORANIMATIONTRANSITION_H
