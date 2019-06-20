#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class WaveAnimation : public Animation {
		public:
			explicit WaveAnimation(Section& section);
			~WaveAnimation() = default;
			int8_t get_skew() const;
			void set_skew(int8_t skew);
			void update();

		private:
			/// The amount to offset each row (or column).
			int8_t skew_ = 0;

			void map();
	};
}

#endif // WAVEANIMATION_H
