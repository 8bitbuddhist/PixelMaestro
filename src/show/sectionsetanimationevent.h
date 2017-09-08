#ifndef SECTIONSETANIMATIONEVENT_H
#define SECTIONSETANIMATIONEVENT_H

#include "../animation/animation.h"
#include "../section.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionSetAnimationEvent : public Event {
		public:
			SectionSetAnimationEvent(unsigned long time, Section* section, Animation* animation);
			SectionSetAnimationEvent(unsigned long time, Section* section, Animation* animations, unsigned int num_animations);
			void run();

		private:
			Animation *animation_ = nullptr;
			unsigned int num_animations_ = 0;
			Section* section_;

	};
}

#endif // SECTIONSETANIMATIONEVENT_H
