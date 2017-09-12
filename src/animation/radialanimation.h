#ifndef RADIALANIMATION_H
#define RADIALANIMATION_H

#include "../core/point.h"
#include "animation.h"

namespace PixelMaestro {
	class RadialAnimation : public Animation {
		public:
			RadialAnimation(Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update(Section* section);

		private:
			/// Tracks the center of the grid.
			Point center_ = {0, 0};

			/// Tracks the distance of the current point from the center.
			unsigned short distance_ = 0;

			/// Stores the size of the array to check for resizes.
			Point size_ = {0, 0};

			/// Stores the slope between a Pixel and the center of the grid.
			unsigned short slope_;

			/// Stores the square of the current x-axis.
			unsigned short y_squared_ = 0;
	};
}

#endif // RADIALANIMATION_H
