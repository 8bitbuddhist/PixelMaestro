#ifndef RANDOMANIMATION_H
#define RANDOMANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class RandomAnimation : public ColorAnimation {
		public:
			RandomAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();
	};
}

#endif // RANDOMANIMATION_H
