#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class BlinkAnimation : public Animation {
		public:
			BlinkAnimation(Section* section, Colors::RGB* colors = nullptr, uint8_t num_colors = 0);
			~BlinkAnimation();
			void update();
	};
}

#endif // BLINKANIMATION_H
