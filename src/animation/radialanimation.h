#ifndef RADIALANIMATION_H
#define RADIALANIMATION_H

#include "../core/point.h"
#include "animation.h"

namespace PixelMaestro {
	class RadialAnimation : public Animation {
		public:
			RadialAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();

		private:
			/// Tracks the center of the grid.
			Point center_ = {0, 0};

			/// Tracks the distance of the current point from the center.
			unsigned short distance_ = 0;

			/// Stores the size of the array to check for resizes.
			Point size = {0, 0};

			// Temporary storage for caluclating distances
			unsigned short x_squared = 0;
			unsigned short y_squared = 0;
	};
}

#endif // RADIALANIMATION_H
