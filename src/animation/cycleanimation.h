#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class CycleAnimation : public Animation {
		public:
			CycleAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned short speed = 100, unsigned short pause = 0);
			~CycleAnimation();
			void update(Section* section);
	};
}

#endif // CYCLEANIMATION_H
