/*
	Pixel.h - Library for controlling a single RGB pixel.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

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
			Colors::RGB update();

		private:
			struct Step {
				int8_t r = 0;
				int8_t g = 0;
				int8_t b = 0;
				uint8_t count = 0;
			};

			/// The Pixel's current color.
			Colors::RGB current_color_ = {0, 0, 0};

			/// Tracks the step from the Pixel's current color to its next color.
			Pixel::Step step_;

	};
}

#endif // PIXEL_H
