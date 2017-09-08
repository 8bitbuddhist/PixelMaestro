#ifndef SECTIONSETANIMATIONEVENT_H
#define SECTIONSETANIMATIONEVENT_H

#include "../animation/animation.h"
#include "../core/section.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionSetAnimationEvent : public Event {
		public:
			SectionSetAnimationEvent(unsigned long time, Section* section, Animation* animation, bool preserve_cycle_index = false);
			SectionSetAnimationEvent(unsigned long time, Section* section, Animation** animations, unsigned int num_animations, bool preserve_cycle_index = false);
			void run();

		private:
			Animation* animation_ = nullptr;
			Animation** animations_ = nullptr;
			unsigned int current_animation_ = 0;
			unsigned int num_animations_ = 0;
			bool preserve_cycle_index_ = false;
			Section* section_;

	};
}

#endif // SECTIONSETANIMATIONEVENT_H
