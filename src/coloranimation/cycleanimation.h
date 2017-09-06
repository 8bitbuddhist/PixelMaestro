#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class CycleAnimation : public ColorAnimation {
		public:
			CycleAnimation(Section* section, bool reverse = false, Orientations orientation = Orientations::HORIZONTAL);
			void update();
	};
}

#endif // CYCLEANIMATION_H
