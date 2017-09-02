#ifndef SECTIONSETOVERLAYEVENT_H
#define SECTIONSETOVERLAYEVENT_H

#include "../colors.h"
#include "../section.h"
#include "event.h"

namespace PixelMaestro {
	class SectionSetOverlayEvent : public Event {
		public:
			SectionSetOverlayEvent(unsigned long time, Section* section, Section::Overlay* overlay);
			SectionSetOverlayEvent(unsigned long time, Section* section, Section* overlay_section, Colors::MixMode mix_mode, float alpha = 0.0);
			void run();

		private:
			Section::Overlay* overlay_;
			Section* section_;
	};
}

#endif // SECTIONSETOVERLAYEVENT_H
