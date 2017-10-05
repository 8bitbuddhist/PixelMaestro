#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class WaveAnimation : public Animation {
		public:
			WaveAnimation(Colors::RGB* colors, uint8_t num_colors);
			~WaveAnimation();
			void update(Section* section);
	};
}

#endif // WAVEANIMATION_H
