#ifndef SECTIONUNSETOVERLAYEVENT_H
#define SECTIONUNSETOVERLAYEVENT_H

#include "../Section.h"
#include "Event.h"

namespace PixelMaestro {
	class SectionUnsetOverlayEvent : public Event {
		public:
			SectionUnsetOverlayEvent(unsigned long time, Section *section);
			void run();

		private:
			Section *section_;
	};
}

#endif // SECTIONUNSETOVERLAYEVENT_H
