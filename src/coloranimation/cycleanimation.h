#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class CycleAnimation : public ColorAnimation {
		public:
			CycleAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();
	};
}

#endif // CYCLEANIMATION_H
