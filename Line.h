/*
	Line.cpp - Library for controlling multiple pixels
	Requires Pixel and Colors libraries

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

#ifndef LINE_H
#define LINE_H

#include "Colors.h"
#include "Pixel.h"

namespace PixelMaestro {
	class Line {

		public:
			enum ColorAnimations {
				NONE,
				SOLID,
				BLINK,
				WAVE,
				PONG,
				MERGE,
				RANDOMINDEX,
				SPARKLE,
				PATTERN,
				CYCLE,
				STATIC
			};

			Line();
			Line(Pixel *pixels, unsigned char numPixels);

			Line::ColorAnimations getColorAnimation();
			unsigned long getCurrentTime();
			bool getFade();
			unsigned char getNumPixels();
			Pixel *getPixel(unsigned char pixel);
			unsigned char getSpeed();
			void setAll(Colors::RGB *color);
			void setColorAnimation(Line::ColorAnimations animation = ColorAnimations(NONE), bool reverseAnimation = false);
			void setColors(Colors::RGB *colors, unsigned char numColors);
			void setCycleIndex(unsigned char index);
			void setOne(unsigned char pixel, Colors::RGB *color);
			void setPattern(unsigned char *pattern, unsigned char patternLength);
			void setPixels(Pixel *pixels, unsigned char numPixels);
			void setUpdateSpeed(unsigned char speed, unsigned char delay = 0);
			void toggleFade();
			void update(unsigned long currentTime);

		private:
			Colors::RGB *colors_;
			unsigned long *current_time_;
			unsigned long cycle_end_;
			unsigned char cycle_index_ = 0;
			unsigned char delay_ = 0;
			bool fade_ = true;
			unsigned long last_time_ = 0;
			Pixel *pixels_;
			Line::ColorAnimations color_animation_ = ColorAnimations(SOLID);
			unsigned char num_colors_;
			unsigned char num_pixels_;
			unsigned char *pattern_;
			unsigned char pattern_length_ = 0;
			bool reverse_animation_ = false;
			unsigned char speed_ = 10;	// Default to 10ms

			// Color animation functions
			void animation_blink();
			void animation_cycle();
			void animation_decrementCycle();
			unsigned char animation_getColorIndex(unsigned char count);
			void animation_incrementCycle();
			void animation_merge();
			void animation_pattern();
			void animation_pong();
			void animation_randomIndex();
			void animation_solid();
			void animation_sparkle();
			void animation_static();
			void animation_wave();
	};
}

#endif
