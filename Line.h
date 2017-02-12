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
			/// Set of animations usable by the Line.
			enum ColorAnimations {
				NONE,			/// Turns off all Pixels in the Line.
				SOLID,			/// Displays the default color of each Pixel.
				BLINK,			/// Alternates Pixels between their default color and black (off).
				WAVE,			/// Scrolls the color array across the Line.
				PONG,			/// Scrolls the color array back and forth in a ping-pong pattern.
				MERGE,			/// Converges colors into the center of the Line.
				RANDOMINDEX,	/// Sets each Pixel to a random color stored in colors_.
				SPARKLE,		/// Creates a shimmering effect by turning on random pixels.
				PATTERN,		/// Scrolls through the pattern set in pattern_.
				CYCLE,			/// Cycles all pixels through all stored colors.
				STATIC			/// Creates a static effect by blending each pixel between varying levels of gray.
			};

			Line();
			Line(Pixel *pixels, unsigned char numPixels);

			Line::ColorAnimations getColorAnimation();
			bool getFade();
			unsigned char getNumPixels();
			Pixel *getPixel(unsigned char pixel);
			unsigned char getUpdateSpeed();
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
			Colors::RGB *colors_;			/// Array of colors stored in the Line.
			unsigned long *current_time_;	/// The current program time. Used to determine when to update the Line.
			unsigned long cycle_end_;		/// The end time of the last cycle. Used to determine when to run the next cycle.
			unsigned char cycle_index_ = 0;	///	The current cycle index.
			unsigned char delay_ = 0;		/// Any delay between cycles.
			bool fade_ = true;				/// Whether to fade between cycles.
			unsigned long last_time_ = 0;	/// The last time the Line was updated. Note that this is different than cycle_end_.
			Pixel *pixels_;					/// Array of Pixels stored in the Line.
			Line::ColorAnimations color_animation_ = ColorAnimations(SOLID);	/// The current Line animation. Defaults to SOLID.
			unsigned char num_colors_;		/// The number of colors in colors_.
			unsigned char num_pixels_;		/// The number of Pixels in pixels_.
			unsigned char *pattern_;		/// The pattern to display when the PATTERN animation is active.
			unsigned char pattern_length_ = 0;	/// The number of pattern elements in pattern_.
			bool reverse_animation_ = false;	/// Whether to reverse the animation in color_animation_.
			unsigned char speed_ = 10;		/// The update speed of the Line (in ms). Defaults to 10.

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
