#ifndef SOLIDANIMATION_H
#define SOLIDANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SolidAnimation : public Animation {
		public:
			SolidAnimation(Colors::RGB* colors = nullptr, uint8_t num_colors = 0, uint16_t speed = 100, uint16_t pause = 0);
			~SolidAnimation();
			void update(Section* section);
	};
}

#endif // SOLIDANIMATION_H
