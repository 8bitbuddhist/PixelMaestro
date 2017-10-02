#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class BlinkAnimation : public Animation {
		public:
			BlinkAnimation(Colors::RGB* colors = nullptr, uint8_t num_colors = 0, uint16_t speed = 100, uint16_t pause = 0);
			~BlinkAnimation();
			void update(Section* section);
	};
}

#endif // BLINKANIMATION_H
