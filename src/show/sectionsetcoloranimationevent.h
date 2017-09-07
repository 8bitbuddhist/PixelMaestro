#ifndef SECTIONSETCOLORANIMATIONEVENT_H
#define SECTIONSETCOLORANIMATIONEVENT_H

#include "../coloranimation.h"
#include "../section.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionSetColorAnimationEvent : public Event {
		public:
			SectionSetColorAnimationEvent(unsigned long time, Section* section, ColorAnimation* animation);
			SectionSetColorAnimationEvent(unsigned long time, Section* section, ColorAnimation* animations, unsigned int num_animations);
			void run();

		private:
			ColorAnimation *animation_ = nullptr;
			ColorAnimation *animations_ = nullptr;
			unsigned int num_animations_;
			Section* section_;

	};
}

#endif // SECTIONSETCOLORANIMATIONEVENT_H
