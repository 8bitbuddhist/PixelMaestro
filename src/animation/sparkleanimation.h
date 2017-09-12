#ifndef SPARKLEANIMATION_H
#define SPARKLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SparkleAnimation : public Animation {
		public:
			SparkleAnimation(Colors::RGB* colors = nullptr, unsigned short num_colors = 0, unsigned char threshold = 50);
			void update(Section* section);

		private:
			/**
			 * Threshold for activating a Pixel (0 - 100).
			 * The higher the threshold, the less likely a Pixel will be activated.
			 */
			unsigned char threshold_;
	};
}

#endif // SPARKLEANIMATION_H
