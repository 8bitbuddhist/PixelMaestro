#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class BlinkAnimation : public Animation {
		public:
			BlinkAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned short speed = 100, unsigned short pause = 0);
			~BlinkAnimation();
			void update(Section* section);
	};
}

#endif // BLINKANIMATION_H
