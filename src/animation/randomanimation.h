#ifndef RANDOMANIMATION_H
#define RANDOMANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class RandomAnimation : public Animation {
		public:
			RandomAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned short speed = 100, unsigned short pause = 0);
			void update(Section* section);
	};
}

#endif // RANDOMANIMATION_H
