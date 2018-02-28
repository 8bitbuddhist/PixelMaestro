#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class WaveAnimation : public Animation {
		public:
			WaveAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~WaveAnimation();
			bool get_mirror() const;
			int8_t get_skew() const;
			void set_mirror(bool mirror);
			void set_skew(int8_t skew);
			void update();

		private:
			/// Whether to mirror the wave across the x or y axis.
			bool mirror_ = false;

			/// The amount to offset each row (or column).
			int8_t skew_ = 0;
	};
}

#endif // WAVEANIMATION_H
