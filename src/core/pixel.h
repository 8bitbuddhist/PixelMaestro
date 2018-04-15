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
			Colors::RGB* get_color();
			void set_next_color(Colors::RGB* next_color, uint8_t step_count);
			void update();

		private:
			/// The Pixel's current color.
			Colors::RGB current_color_;

			/// The Pixel's target color.
			Colors::RGB* next_color_ = nullptr;

			/// The size of each step from the Pixel's current color to its next color.
			int8_t step_[3] = {0, 0, 0};

			/// The number of steps from the current color to the next color.
			uint8_t step_count_ = 0;

	};
}

#endif // PIXEL_H
