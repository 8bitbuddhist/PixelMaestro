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
#include "Section.h"

namespace PixelMaestro {
	class Maestro {
		public:
			Maestro(Pixel *pixels, unsigned char numPixels, Section *sections, unsigned char numSections);
			Section *getSection(unsigned char section);
			unsigned char getNumSections();
			bool getRunning();
			unsigned char getUpdateSpeed();
			void setSections(Section *sections, unsigned char numSections);
			void toggleRunning();
			void update(unsigned long currentTime);

		private:
			Pixel *pixels_;				/// Array of Pixels managed by the Maestro.
			unsigned char num_pixels_;	/// Number of Pixels managed by the Maestro.
			bool running_ = true;		/// Active state of the Maestro.
			Section *sections_;			/// Array of Sections managed by the Maestro.
			unsigned char num_sections_;	/// Number of Sections managed by the Maestro.
	};
}

#endif
