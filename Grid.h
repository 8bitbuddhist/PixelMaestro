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
			Grid(Line *lines, unsigned char numLines);

			Line *getLine(unsigned char row);
			void setUpdateSpeed(unsigned char speed, unsigned char delay = 0);
			void toggleFade();
			void update(unsigned long currentTime);

		private:
			Line *lines_;
			unsigned char num_lines_;
	};
}

#endif
