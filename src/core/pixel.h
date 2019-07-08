/*
	Pixel.h - Class for controlling a single RGB LED.
*/

// #define PIXEL_DISABLE_FADING			// Disables per-Pixel fading. Restores 3 bytes per Pixel.
// #define PIXEL_ENABLE_ACCURATE_FADING	// Enables tracking of the Pixel's next color. Only available when PIXEL_DISABLE_FADING is not enabled. Uses 3 bytes per Pixel.

#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include "colors.h"

namespace PixelMaestro {
	class Pixel {

		public:
			Pixel() {}
			void clear();
			Colors::RGB& get_color();
			void set_next_color(const Colors::RGB& next_color, uint8_t step_count);
			void update(bool apply_next_color = false);

		private:

			/// The Pixel's current color.
			Colors::RGB current_color_ = {0, 0, 0};

			#ifndef PIXEL_DISABLE_FADING
				/// The amount to increment current_color_ for each step when fading.
				Colors::RGB step_ = {0, 0, 0};

				#ifdef PIXEL_ENABLE_ACCURATE_FADING
					/// The Pixel's target color.
					Colors::RGB next_color_ = {0, 0, 0};
				#endif
			#endif

	};
}

#endif // PIXEL_H
