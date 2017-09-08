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
			unsigned short get_num_sections();
			unsigned short get_refresh_rate();
			bool get_running();
			Section* get_section(unsigned short section);
			void set_sections(Section* sections, unsigned short num_sections);
			void toggle_running();
			void update(const unsigned long& current_time);

		private:
			/// Active running state of the Maestro.
			bool running_ = true;

			/// Sections managed by the Maestro.
			Section* sections_;

			/// Number of Sections managed by the Maestro.
			unsigned short num_sections_;
	};
}

#endif
