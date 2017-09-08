#ifndef SECTIONSETCANVASEVENT_H
#define SECTIONSETCANVASEVENT_H

#include "../core/section.h"
#include "event.h"

namespace PixelMaestro {
	class SectionSetCanvasEvent : public Event {
		public:
			SectionSetCanvasEvent(unsigned long time, Section* section, Canvas* canvas);
			void run();

		private:
			Canvas* canvas_;
			Section* section_;
	};
}

#endif // SECTIONSETCANVASEVENT_H
