/*
	Pixel.h - Library for controlling a single RGB pixel
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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
			void setNextColor(Colors::RGB *nextColor, bool fade, unsigned char interval);
			void update();

		private:
			Colors::RGB current_color_ = Colors::BLACK;
			Colors::RGB *next_color_ = &Colors::BLACK;
			Colors::RGB *previous_color_ = &Colors::BLACK;
			unsigned char step_size_[3] = {0, 0, 0};
			unsigned char step_count_ = 0;
	};
}

#endif // PIXEL_H
