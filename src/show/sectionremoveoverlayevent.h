#ifndef SECTIONREMOVEOVERLAYEVENT_H
#define SECTIONREMOVEOVERLAYEVENT_H

#include "../core/section.h"
#include "event.h"

namespace PixelMaestro {
	class SectionRemoveOverlayEvent : public Event {
		public:
			SectionRemoveOverlayEvent(unsigned long time, Section* section);
			void run();

		private:
			Section* section_;
	};
}

#endif // SECTIONREMOVEOVERLAYEVENT_H
