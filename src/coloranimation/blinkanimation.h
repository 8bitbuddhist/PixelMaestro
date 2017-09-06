#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class BlinkAnimation : public ColorAnimation {
		public:
			BlinkAnimation(Section* section, bool reverse = false, Orientations orientation = Orientations::HORIZONTAL);
			void update();
	};
}

#endif // BLINKANIMATION_H
