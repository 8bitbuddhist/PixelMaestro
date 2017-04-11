/*
	Pixel.h - Library for controlling a single RGB pixel.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

#ifndef PIXEL_H
#define PIXEL_H

#include "Colors.h"

namespace PixelMaestro {
	class Pixel {

		public:
			Colors::RGB *getColor();
			Colors::RGB *getNextColor();
			unsigned char getStepCount();
			void setNextColor(Colors::RGB *nextColor, bool fade, unsigned short cycleSpeed, unsigned short refreshRate);
			void update();

		private:
			Colors::RGB current_color_ = Colors::BLACK;
			Colors::RGB *next_color_ = &Colors::BLACK;
			Colors::RGB step_ = {0, 0, 0};
			unsigned char step_count_ = 0;
	};
}

#endif // PIXEL_H
