#ifndef SECTIONSETCOLORANIMATIONEVENT_H
#define SECTIONSETCOLORANIMATIONEVENT_H

#include "../section.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionSetColorAnimationEvent : public Event {
		public:
			SectionSetColorAnimationEvent(unsigned long time, Section* section, Section::ColorAnimations animation_, bool reverse_animation, Section::AnimationOrientations orientation);
			SectionSetColorAnimationEvent(unsigned long time, Section* section, Section::ColorAnimations *animations, unsigned int num_animations, bool reverse_animation, Section::AnimationOrientations orientation);
			void run();

		private:
			Section::ColorAnimations animation_;
			Section::ColorAnimations *animations_ = nullptr;
			unsigned int num_animations_;
			Section::AnimationOrientations orientation;
			bool reverse_animation;
			Section* section_;

	};
}

#endif // SECTIONSETCOLORANIMATIONEVENT_H
