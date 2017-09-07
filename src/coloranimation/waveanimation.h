#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class WaveAnimation : public ColorAnimation {
		public:
			WaveAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();
	};
}

#endif // WAVEANIMATION_H
