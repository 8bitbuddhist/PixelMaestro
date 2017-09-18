#ifndef OVERLAYSETOPTIONSEVENT_H
#define OVERLAYSETOPTIONSEVENT_H

#include "../core/colors.h"
#include "../core/section.h"
#include "event.h"

namespace PixelMaestro {
	class OverlaySetOptionsEvent : public Event {
		public:
			OverlaySetOptionsEvent(unsigned long time, Section::Overlay* overlay, Colors::MixMode mix_mode, unsigned char alpha);
			void run();

		private:
			unsigned char alpha_;
			Colors::MixMode mix_mode_;
			Section::Overlay* overlay_;
	};
}

#endif // OVERLAYSETOPTIONSEVENT_H
