/*
	Maestro.cpp - Library for controlling multiple collections (Grids or Lines) of RGB LEDs.

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

#ifndef MAESTRO_H
#define MAESTRO_H

#include "Colors.h"
#include "Grid.h"

namespace PixelMaestro {
	class Maestro {
		public:
			Maestro(Grid *grids, unsigned char numGrids);
			Maestro(Line *lines, unsigned char numLines);
			Maestro(Line *lines, unsigned char numLines, Grid *grids, unsigned char numGrids);
			Grid *getGrid(unsigned char grid);
			Line *getLine(unsigned char line);
			unsigned char getNumGrids();
			unsigned char getNumLines();
			bool getRunning();
			unsigned char getUpdateSpeed();
			void setGrids(Grid *grids, unsigned char numGrids);
			void setLines(Line *lines, unsigned char numLines);
			void toggleRunning();
			void update(unsigned long currentTime);

		private:
			Grid *grids_;	/// Collection of Grids managed by the Maestro.
			Line *lines_;	/// Collection of Lines managed by the Maestro.
			unsigned char num_grids_ = 0;	/// Number of Grids in grids_.
			unsigned char num_lines_ = 0;	/// Number of Lines in lines_.
			bool running_ = true;			/// Active state of the Maestro.
	};
}

#endif
