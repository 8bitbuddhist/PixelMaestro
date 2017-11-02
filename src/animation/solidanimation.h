#ifndef SOLIDANIMATION_H
#define SOLIDANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SolidAnimation : public Animation {
		public:
			SolidAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~SolidAnimation();
			void update();
	};
}

#endif // SOLIDANIMATION_H
