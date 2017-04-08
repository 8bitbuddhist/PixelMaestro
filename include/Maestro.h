/*
	Maestro.cpp - Library for controlling collections of Pixels.
*/

#ifndef MAESTRO_H
#define MAESTRO_H

#include "Colors.h"
#include "Section.h"

namespace PixelMaestro {
	class Maestro {
		public:
			Maestro(Section *sections, unsigned short numSections);
			unsigned short getNumSections();
			bool getRunning();
			Section *getSection(unsigned short section);
			unsigned char getUpdateSpeed();
			void setSections(Section *sections, unsigned short numSections);
			void toggleRunning();
			void update(unsigned long currentTime);

		private:
			bool running_ = true;	/// Active state of the Maestro.
			Section *sections_;		/// Array of Sections managed by the Maestro.
			unsigned short num_sections_;	/// Number of Sections managed by the Maestro.
	};
}

#endif
