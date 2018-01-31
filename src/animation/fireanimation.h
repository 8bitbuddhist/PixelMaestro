#ifndef FIREANIMATION_H
#define FIREANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class FireAnimation : public Animation {
		public:
			FireAnimation(Section* section, Colors::RGB* colors = nullptr, uint8_t num_colors = 0);
			~FireAnimation();
			uint8_t get_divisor();
			uint8_t get_multiplier();
			void set_divisor(uint8_t divisor);
			void set_multiplier(uint8_t multiplier);
			void update();

		private:
			uint8_t** color_indices_ = nullptr;

			uint8_t multiplier_ = 32;

			uint8_t divisor_ = 129;
	};
}

#endif // FIREANIMATION_H