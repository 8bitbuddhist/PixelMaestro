#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class WaveAnimation : public Animation {
		public:
			WaveAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~WaveAnimation();
			void update();
	};
}

#endif // WAVEANIMATION_H
