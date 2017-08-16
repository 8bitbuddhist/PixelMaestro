#ifndef SECTIONTOGGLEFADINGEVENT_H
#define SECTIONTOGGLEFADINGEVENT_H

#include "../Section.h"
#include "Event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionToggleFadeEvent : public Event {
		public:
			SectionToggleFadeEvent(unsigned long time, Section *section);
			void run();

		private:
			Section *section_;
	};
}

#endif // SECTIONTOGGLEFADINGEVENT_H
