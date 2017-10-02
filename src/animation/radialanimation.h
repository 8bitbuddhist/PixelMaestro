#ifndef RADIALANIMATION_H
#define RADIALANIMATION_H

#include "../core/point.h"
#include "animation.h"

namespace PixelMaestro {
	class RadialAnimation : public Animation {
		public:
			RadialAnimation(Colors::RGB* colors = nullptr, uint8_t num_colors = 0, uint16_t speed = 100, uint16_t pause = 0);
			~RadialAnimation();
			void update(Section* section);

		private:
			/// Tracks the center of the grid.
			Point center_ = {0, 0};

			/// Tracks the distance of the current point from the center.
			uint16_t distance_ = 0;

			/// Stores the size of the array to check for resizes.
			Point size_ = {0, 0};

			/// Stores the slope between a Pixel and the center of the grid.
			uint16_t slope_;

			/// Stores the square of the current x-axis.
			uint16_t y_squared_ = 0;
	};
}

#endif // RADIALANIMATION_H
