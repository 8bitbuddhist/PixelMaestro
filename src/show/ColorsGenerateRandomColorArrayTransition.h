#ifndef COLORSGENERATERANDOMCOLORARRAYTRANSITION_H
#define COLORSGENERATERANDOMCOLORARRAYTRANSITION_H

#include "../Colors.h"
#include "Transition.h"

namespace PixelMaestro {
	class ColorsGenerateRandomColorArrayTransition : public Transition {
		public:
			ColorsGenerateRandomColorArrayTransition(unsigned long time, Colors::RGB *newArray, Colors::RGB *baseColor, unsigned int numColors, float range = 1.0);
			void run();

		private:
			Colors::RGB *new_array_;
			Colors::RGB *base_color_;
			unsigned int num_colors_;
			float range_;

	};
}

#endif // COLORSGENERATERANDOMCOLORARRAYTRANSITION_H
