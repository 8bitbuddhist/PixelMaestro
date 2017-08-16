#ifndef COLORSGENERATERANDOMCOLOR_H
#define COLORSGENERATERANDOMCOLOR_H

#include "../Colors.h"
#include "Event.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorEvent : public Event {
		public:
			ColorsGenerateRandomColorEvent(unsigned long time, Colors::RGB *color);
			ColorsGenerateRandomColorEvent(unsigned long time, Colors::RGB *color, Colors::RGB *selection, unsigned int numOptions);
			void run();

		private:
			Colors::RGB *color_;
			unsigned int num_options_;
			Colors::RGB *selection_ = nullptr;
	};
}

#endif // COLORSGENERATERANDOMCOLOR_H
