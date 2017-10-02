#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class CycleAnimation : public Animation {
		public:
			CycleAnimation(Colors::RGB* colors = nullptr, uint8_t num_colors = 0, uint16_t speed = 100, uint16_t pause = 0);
			~CycleAnimation();
			void update(Section* section);
	};
}

#endif // CYCLEANIMATION_H
