#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class BlinkAnimation : public Animation {
		public:
			explicit BlinkAnimation(Section& section);
			~BlinkAnimation() = default;
			void map();
			void update();
	};
}

#endif // BLINKANIMATION_H
