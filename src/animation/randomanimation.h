#ifndef RANDOMANIMATION_H
#define RANDOMANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class RandomAnimation : public Animation {
		public:
			RandomAnimation(Colors::RGB* colors = nullptr, uint8_t num_colors = 0, uint16_t speed = 100, uint16_t pause = 0);
			~RandomAnimation();
			void update(Section* section);
	};
}

#endif // RANDOMANIMATION_H
