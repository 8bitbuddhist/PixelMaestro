#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class BlinkAnimation : public ColorAnimation {
		public:
			BlinkAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();
	};
}

#endif // BLINKANIMATION_H
