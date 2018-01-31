#ifndef FIREANIMATION_H
#define FIREANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class FireAnimation : public Animation {
		public:
			FireAnimation(Section* section, Colors::RGB* colors = nullptr, uint8_t num_colors = 0);
			~FireAnimation();
			uint8_t get_multiplier();
			void reset_color_indices(Point* dimensions);
			void set_multiplier(uint8_t multiplier);
			void update();

		private:
			/**
			 * Stores the index of the corresponding Palette color for each Pixel.
			 * This is needed to track the movement of flames through the grid.
			 */
			uint8_t** buffer_ = nullptr;

			/// Tracks the size of the Pixel grid.
			Point dimensions_ = Point(0, 0);

			/// Sets the size of the flames (larger value = bigger flames).
			uint8_t multiplier_ = 48;
	};
}

#endif // FIREANIMATION_H