#ifndef COLORSGENERATERANDOMCOLOR_H
#define COLORSGENERATERANDOMCOLOR_H

#include "../Colors.h"
#include "Transition.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorTransition : public Transition {
		public:
			ColorsGenerateRandomColorTransition(unsigned long time, Colors::RGB *color);
			void run();

		private:
			Colors::RGB *color_;
	};
}

#endif // COLORSGENERATERANDOMCOLOR_H
