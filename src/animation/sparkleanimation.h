#ifndef SPARKLEANIMATION_H
#define SPARKLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SparkleAnimation : public Animation {
		public:
			SparkleAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned char threshold = 25);
			void set_threshold(unsigned char threshold);
			void update(Section* section);

		private:
			/**
			 * Threshold for activating a Pixel (0 - 100).
			 * The higher the threshold, the more likely a Pixel will be activated.
			 */
			unsigned char threshold_;
	};
}

#endif // SPARKLEANIMATION_H
