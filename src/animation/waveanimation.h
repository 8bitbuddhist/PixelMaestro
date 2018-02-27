#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class WaveAnimation : public Animation {
		public:
			WaveAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~WaveAnimation();
			bool get_merge() const;
			int8_t get_skew() const;
			void set_merge(bool merge);
			void set_skew(int8_t skew);
			void update();

		private:
			/// Whether to merge the wave into the center of the grid.
			bool merge_ = false;

			/// The amount to offset each row (or column).
			int8_t skew_ = 0;
	};
}

#endif // WAVEANIMATION_H
