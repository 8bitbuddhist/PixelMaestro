#ifndef COLORSGENERATERANDOMCOLOR_H
#define COLORSGENERATERANDOMCOLOR_H

#include "../colors.h"
#include "event.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorEvent : public Event {
		public:
			ColorsGenerateRandomColorEvent(unsigned long time, Colors::RGB* color);
			ColorsGenerateRandomColorEvent(unsigned long time, Colors::RGB* color, Colors::RGB* selection, unsigned int num_options);
			void run();

		private:
			Colors::RGB* color_;
			unsigned int num_options_;
			Colors::RGB* selection_ = nullptr;
	};
}

#endif // COLORSGENERATERANDOMCOLOR_H
