#ifndef SECTIONADDOVERLAYEVENT_H
#define SECTIONADDOVERLAYEVENT_H

#include "../core/colors.h"
#include "../core/section.h"
#include "event.h"

namespace PixelMaestro {
	class SectionAddOverlayEvent : public Event {
		public:
			SectionAddOverlayEvent(unsigned long time, Section* section, Colors::MixMode mix_mode = Colors::MixMode::NORMAL, unsigned char alpha = 128);
			void run();

		private:
			unsigned char alpha_;
			Colors::MixMode mix_mode_;
			Section* section_;
	};
}

#endif // SECTIONADDOVERLAYEVENT_H
