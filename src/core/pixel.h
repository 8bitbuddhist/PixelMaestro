/*
	Pixel.h - Library for controlling a single RGB pixel.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

// #define DISABLE_COLOR_BUFFER // Disable per-Pixel fading and color buffering.

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
			void update();

		private:

			/// The Pixel's current color.
			Colors::RGB current_color_ = {0, 0, 0};

			#ifndef DISABLE_COLOR_BUFFER
				/// The amount to increment current_color_ for each step when fading.
				Colors::RGB step_ = {0, 0, 0};
			#endif // DISABLE_COLOR_BUFFER

	};
}

#endif // PIXEL_H
