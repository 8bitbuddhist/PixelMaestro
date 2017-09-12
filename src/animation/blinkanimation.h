#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class BlinkAnimation : public Animation {
		public:
			BlinkAnimation(Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update(Section* section);
	};
}

#endif // BLINKANIMATION_H
