#ifndef COLORSGENERATERANDOMCOLOR_H
#define COLORSGENERATERANDOMCOLOR_H

#include "../Colors.h"
#include "Transition.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorTransition : public Transition {
		public:
			ColorsGenerateRandomColorTransition(Colors::RGB *color, unsigned long time);
			void run();

		private:
			Colors::RGB *color_;
	};
}

#endif // COLORSGENERATERANDOMCOLOR_H
