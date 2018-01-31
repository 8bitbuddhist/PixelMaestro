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
			void reset_color_indices(Point* dimensions);
			void set_divisor(uint8_t divisor);
			void set_multiplier(uint8_t multiplier);
			void update();

		private:
			/**
			 * Tracks the index of the corresponding Palette color for each Pixel.
			 * This is needed to move the flames up through the grid.
			 */
			uint8_t** buffer_ = nullptr;

			/// Tracks the size of the Pixel grid.
			Point dimensions_ = Point(0, 0);

			/// Determines part of the frame calculation (resolution?)
			uint8_t multiplier_ = 32;

			/// Determines the max height of the flames (larger value = lower flames).
			uint8_t divisor_ = 129;
	};
}

#endif // FIREANIMATION_H