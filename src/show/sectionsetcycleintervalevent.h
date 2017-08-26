#ifndef SECTIONSETCYCLEINTERVAL_H
#define SECTIONSETCYCLEINTERVAL_H

#include "../section.h"
#include "event.h"

namespace PixelMaestro {
	class SectionSetCycleIntervalEvent : public Event {
		public:
			SectionSetCycleIntervalEvent(unsigned long time, Section* section, unsigned short interval, unsigned short pause = 0);
			void run();

		private:
			Section* section_;
			unsigned short interval_;
			unsigned short pause_;
	};
}

#endif // SECTIONSETCYCLEINTERVAL_H
