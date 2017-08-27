/*
	Pixel.h - Library for controlling a single RGB pixel.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

#ifndef PIXEL_H
#define PIXEL_H

#include "colors.h"

namespace PixelMaestro {
	class Pixel {

		public:
			Colors::RGB* get_color();
			void set_next_color(Colors::RGB* next_color, bool fade, unsigned short cycle_speed, unsigned short refresh_rate);
			void update();

		private:
			/// The Pixel's current color. Defaults to BLACK.
			Colors::RGB current_color_ = Colors::BLACK;

			/// The Pixel's next (i.e. target) color.
			Colors::RGB* next_color_ = &Colors::BLACK;

			/// The size of each step from current_color_ to next_color_ (only applicable when fading).
			Colors::RGB step_ = {0, 0, 0};

			/// The number of steps from current_color_ to next_color_ (only applicable when fading).
			unsigned char step_count_ = 0;
	};
}

#endif // PIXEL_H
