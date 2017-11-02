#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class CycleAnimation : public Animation {
		public:
			CycleAnimation(Section* section, Colors::RGB* colors = nullptr, uint8_t num_colors = 0);
			~CycleAnimation();
			void update();
	};
}

#endif // CYCLEANIMATION_H
