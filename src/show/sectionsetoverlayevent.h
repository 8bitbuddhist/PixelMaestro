#ifndef SECTIONSETOVERLAYEVENT_H
#define SECTIONSETOVERLAYEVENT_H

#include "../core/colors.h"
#include "../core/section.h"
#include "event.h"

namespace PixelMaestro {
	class SectionSetOverlayEvent : public Event {
		public:
			SectionSetOverlayEvent(unsigned long time, Section* section, Section::Overlay* overlay);
			void run();

		private:
			Section::Overlay* overlay_;
			Section* section_;
	};
}

#endif // SECTIONSETOVERLAYEVENT_H
