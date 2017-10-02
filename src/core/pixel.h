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
			Colors::RGB* get_color();
			void set_next_color(Colors::RGB* next_color, bool fade, uint16_t cycle_speed, uint16_t refresh_rate);
			void update();

		private:
			/// The Pixel's current color. Defaults to BLACK.
			Colors::RGB current_color_ = Colors::BLACK;

			/// The Pixel's next (i.e. target) color.
			Colors::RGB* next_color_ = &Colors::BLACK;

			/// The size of each step from current_color_ to next_color_ (only applicable when fading).
			Colors::RGB step_ = Colors::BLACK;

			/// The number of steps from current_color_ to next_color_ (only applicable when fading).
			uint8_t step_count_ = 0;

	};
}

#endif // PIXEL_H
