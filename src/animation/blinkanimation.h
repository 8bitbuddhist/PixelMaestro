#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class BlinkAnimation : public Animation {
		public:
			BlinkAnimation(Section* section);
			~BlinkAnimation();
			void update();

		private:
			Colors::RGB black_ = {0,0,0};
	};
}

#endif // BLINKANIMATION_H
