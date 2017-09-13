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
			Maestro(Section* sections, unsigned short num_sections);
			Colors::RGB get_pixel_color(unsigned short section, unsigned int pixel);
			unsigned short get_num_sections();
			unsigned short get_refresh_interval();
			bool get_running();
			Section* get_section(unsigned short section);
			void set_brightness(float brightness);
			void set_cycle_interval(unsigned short interval, unsigned short pause = 0);
			void set_running(bool running);
			void set_sections(Section* sections, unsigned short num_sections);
			void update(const unsigned long& current_time);

		private:
			/// Sets the global brightness level. Defaults to 1.0 or 100% brightness.
			float brightness_ = 1.0;

			/// Number of Sections managed by the Maestro.
			unsigned short num_sections_;

			/// Active running state of the Maestro.
			bool running_ = true;

			/// Sections managed by the Maestro.
			Section* sections_;
	};
}

#endif
