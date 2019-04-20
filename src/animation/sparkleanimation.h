#ifndef SPARKLEANIMATION_H
#define SPARKLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SparkleAnimation : public Animation {
		public:
			explicit SparkleAnimation(Section& section);
			~SparkleAnimation() = default;
			uint8_t get_threshold() const;
			void set_threshold(uint8_t threshold);
			void map();
			void update();

		private:
			/**
			 * Threshold for activating a Pixel (0 - 255).
			 * The higher the threshold, the more likely a Pixel will be activated.
			 */
			uint8_t threshold_ = 25;
	};
}

#endif // SPARKLEANIMATION_H
