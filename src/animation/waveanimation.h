#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class WaveAnimation : public Animation {
		public:
			WaveAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned short speed = 100, unsigned short pause = 0);
			~WaveAnimation();
			void update(Section* section);
	};
}

#endif // WAVEANIMATION_H
