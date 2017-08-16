#ifndef SECTIONSETOVERLAYEVENT_H
#define SECTIONSETOVERLAYEVENT_H

#include "../Colors.h"
#include "../Section.h"
#include "Event.h"

namespace PixelMaestro {
	class SectionSetOverlayEvent : public Event {
		public:
			SectionSetOverlayEvent(unsigned long time, Section *section, Section::Overlay *overlay);
			SectionSetOverlayEvent(unsigned long time, Section *section, Section *overlaySection, Colors::MixMode mixMode, float alpha = 0.0);
			void run();

		private:
			Section::Overlay *overlay_;
			Section *section_;
	};
}

#endif // SECTIONSETOVERLAYEVENT_H
