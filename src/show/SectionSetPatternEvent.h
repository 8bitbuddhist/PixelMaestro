#ifndef SECTIONSETPATTERNEVENT_H
#define SECTIONSETPATTERNEVENT_H

#include "../Section.h"
#include "Event.h"

namespace PixelMaestro {
	class SectionSetPatternEvent : public Event {
		public:
			SectionSetPatternEvent(unsigned long time, Section *section, Section::Pattern *pattern);
			void run();

		private:
			Section::Pattern *pattern_;
			Section *section_;
	};
}

#endif // SECTIONSETPATTERNEVENT_H
