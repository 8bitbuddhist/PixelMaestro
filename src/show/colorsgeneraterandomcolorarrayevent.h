#ifndef COLORSGENERATERANDOMCOLORARRAYEVENT_H
#define COLORSGENERATERANDOMCOLORARRAYEVENT_H

#include "../core/colors.h"
#include "event.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorArrayEvent : public Event {
		public:
			ColorsGenerateRandomColorArrayEvent(unsigned long time, Colors::RGB* new_array, Colors::RGB* base_color, unsigned int num_colors, float range = 1.0);
			void run();

		private:
			Colors::RGB* base_color_;
			Colors::RGB* new_array_;
			unsigned int num_colors_;
			float range_;

	};
}

#endif // COLORSGENERATERANDOMCOLORARRAYEVENT_H
