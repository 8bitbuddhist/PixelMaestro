#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class WaveAnimation : public Animation {
		public:
			WaveAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~WaveAnimation();
			uint8_t get_skew();
			void set_skew(uint8_t skew);
			void update();

		private:
			/// The amount to offset each row (or column).
			uint8_t skew_ = 0;
	};
}

#endif // WAVEANIMATION_H
