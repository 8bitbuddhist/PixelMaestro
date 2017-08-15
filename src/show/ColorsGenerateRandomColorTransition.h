#ifndef COLORSGENERATERANDOMCOLOR_H
#define COLORSGENERATERANDOMCOLOR_H

#include "../Colors.h"
#include "Transition.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorTransition : public Transition {
		public:
			ColorsGenerateRandomColorTransition(unsigned long time, Colors::RGB *color);
			ColorsGenerateRandomColorTransition(unsigned long time, Colors::RGB *color, Colors::RGB *selection, unsigned int numOptions);
			void run();

		private:
			Colors::RGB *color_;
			unsigned int num_options_;
			Colors::RGB *selection_ = nullptr;
	};
}

#endif // COLORSGENERATERANDOMCOLOR_H
