#ifndef COLORSGENERATERANDOMCOLORARRAYEVENT_H
#define COLORSGENERATERANDOMCOLORARRAYEVENT_H

#include "../Colors.h"
#include "Event.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorArrayEvent : public Event {
		public:
			ColorsGenerateRandomColorArrayEvent(unsigned long time, Colors::RGB *newArray, Colors::RGB *baseColor, unsigned int numColors, float range = 1.0);
			void run();

		private:
			Colors::RGB *new_array_;
			Colors::RGB *base_color_;
			unsigned int num_colors_;
			float range_;

	};
}

#endif // COLORSGENERATERANDOMCOLORARRAYEVENT_H
