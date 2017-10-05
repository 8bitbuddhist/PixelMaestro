#ifndef RANDOMANIMATION_H
#define RANDOMANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class RandomAnimation : public Animation {
		public:
			RandomAnimation(Colors::RGB* colors, uint8_t num_colors);
			~RandomAnimation();
			void update(Section* section);
	};
}

#endif // RANDOMANIMATION_H
