#ifndef SPARKLEANIMATION_H
#define SPARKLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SparkleAnimation : public Animation {
		public:
			SparkleAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors, uint8_t threshold = 25);
			~SparkleAnimation();
			uint8_t get_threshold();
			void set_threshold(uint8_t threshold);
			void update();

		private:
			/**
			 * Threshold for activating a Pixel (0 - 100).
			 * The higher the threshold, the more likely a Pixel will be activated.
			 */
			uint8_t threshold_;
	};
}

#endif // SPARKLEANIMATION_H
