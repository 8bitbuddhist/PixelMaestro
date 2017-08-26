#ifndef SECTIONUNSETOVERLAYEVENT_H
#define SECTIONUNSETOVERLAYEVENT_H

#include "../section.h"
#include "event.h"

namespace PixelMaestro {
	class SectionUnsetOverlayEvent : public Event {
		public:
			SectionUnsetOverlayEvent(unsigned long time, Section* section);
			void run();

		private:
			Section* section_;
	};
}

#endif // SECTIONUNSETOVERLAYEVENT_H
