#ifndef SOLIDANIMATION_H
#define SOLIDANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SolidAnimation : public Animation {
		public:
			SolidAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned short speed = 100, unsigned short pause = 0);
			void update(Section* section);
	};
}

#endif // SOLIDANIMATION_H
