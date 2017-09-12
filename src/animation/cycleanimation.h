#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class CycleAnimation : public Animation {
		public:
			CycleAnimation(Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update(Section* section);
	};
}

#endif // CYCLEANIMATION_H
