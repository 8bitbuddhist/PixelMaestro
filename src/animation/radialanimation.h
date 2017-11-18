#ifndef RADIALANIMATION_H
#define RADIALANIMATION_H

#include "../core/point.h"
#include "animation.h"

namespace PixelMaestro {
	class RadialAnimation : public Animation {
		public:
			RadialAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~RadialAnimation();
			uint8_t get_resolution();
			void set_resolution(uint8_t resolution);
			void update();

		private:
			/// Tracks the distance of the current point from the center.
			uint16_t distance_ = 0;

			/// In vertical mode, this defines the wideness of each spoke coming from the center.
			uint8_t resolution_ = 10;

			/// Stores the slope between a Pixel and the center of the grid.
			uint16_t slope_;

			/// Stores the square of the current x-axis.
			uint16_t y_squared_ = 0;
	};
}

#endif // RADIALANIMATION_H
