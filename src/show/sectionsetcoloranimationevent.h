#ifndef SECTIONSETCOLORANIMATIONEVENT_H
#define SECTIONSETCOLORANIMATIONEVENT_H

#include "../animation/animation.h"
#include "../section.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionSetColorAnimationEvent : public Event {
		public:
			SectionSetColorAnimationEvent(unsigned long time, Section* section, Animation* animation);
			SectionSetColorAnimationEvent(unsigned long time, Section* section, Animation* animations, unsigned int num_animations);
			void run();

		private:
			Animation *animation_ = nullptr;
			Animation *animations_ = nullptr;
			unsigned int num_animations_;
			Section* section_;

	};
}

#endif // SECTIONSETCOLORANIMATIONEVENT_H
