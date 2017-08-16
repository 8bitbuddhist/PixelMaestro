#ifndef SECTIONSETOVERLAYEVENT_H
#define SECTIONSETOVERLAYEVENT_H

#include "../Colors.h"
#include "../Section.h"
#include "Event.h"

namespace PixelMaestro {
	class SectionSetOverlayEvent : public Event {
		public:
			SectionSetOverlayEvent(unsigned long time, Section *section, Section *overlay, Colors::MixMode mixMode, float alpha = 0.0);
			void run();

		private:
			float alpha_;
			Colors::MixMode mix_mode_;
			Section *overlay_;
			Section *section_;
	};
}

#endif // SECTIONSETOVERLAYEVENT_H
