/*
	Maestro.cpp - Library for controlling collections of Pixels.
*/

#ifndef MAESTRO_H
#define MAESTRO_H

#include "colors.h"
#include "section.h"

namespace PixelMaestro {
	class Maestro {

		public:
			unsigned short getNumSections();
			unsigned short getRefreshRate();
			bool getRunning();
			Section *getSection(unsigned short section);
			void setSections(Section *sections, unsigned short numSections);
			void toggleRunning();
			void update(const unsigned long &currentTime);

		private:
			/// Active running state of the Maestro.
			bool running_ = true;

			/// Sections managed by the Maestro.
			Section *sections_;

			/// Number of Sections managed by the Maestro.
			unsigned short num_sections_;
	};
}

#endif
