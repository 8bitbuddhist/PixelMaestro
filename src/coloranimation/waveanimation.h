#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class WaveAnimation : public ColorAnimation {
		public:
			WaveAnimation(Section* section, bool reverse = false, Orientations orientation = Orientations::HORIZONTAL);
			void update();
	};
}

#endif // WAVEANIMATION_H
