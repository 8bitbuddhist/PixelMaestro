#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class CycleAnimation : public Animation {
		public:
			explicit CycleAnimation(Section* section);
			~CycleAnimation();
			void update();
	};
}

#endif // CYCLEANIMATION_H
