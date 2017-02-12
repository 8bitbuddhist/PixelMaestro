/*
	Grid.cpp - Library for controlling multiple lines of pixels.
	Requires Line library.

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

#ifndef GRID_H
#define GRID_H

#include "Line.h"

namespace PixelMaestro {
	class Grid {
		public:
			/// Set of animations usable by the Grid.
			enum ColorAnimations {
				NONE,		/// Turns off all Pixels in the Grid.
				SOLID,		/// Displays the default color of each Pixel.
				BLINK,		/// Alternates Pixels between their default color and black (off).
				STRIPES		/// Scrolls each Line in alternating directions.
			};
			Grid();
			Grid(Line *lines, unsigned char numLines);

			Line *getLine(unsigned char row);
			unsigned char getNumLines();
			void setColorAnimation(Grid::ColorAnimations animation = ColorAnimations(NONE), bool reverseAnimation = false);
			void setColors(Colors::RGB *colors, unsigned char numColors);
			void setLines(Line *lines, unsigned char numLines);
			void setPixels(Pixel *pixels, unsigned char pixelsPerLine);
			void setUpdateSpeed(unsigned char speed, unsigned char delay = 0);
			void toggleFade();
			void update(unsigned long currentTime);

		private:
			ColorAnimations color_animation_ = ColorAnimations(SOLID);	/// Current color animation (defaults to SOLID).
			Line *lines_;				/// Collection of Lines in the Grid.
			unsigned char num_lines_;	/// Number of Lines in the Grid.
	};
}

#endif
