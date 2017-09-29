/*
	Maestro.cpp - Master class for coordinating Sections.
*/

#ifndef MAESTRO_H
#define MAESTRO_H

#include "../cue/cuecontroller.h"
#include "../cue/event.h"
#include "../cue/show.h"
#include "colors.h"
#include "section.h"

namespace PixelMaestro {
	class CueController;
	class Event;
	class Show;
	class Maestro {

		public:
			Maestro(Section* sections, unsigned char num_sections);
			~Maestro();
			CueController* add_cue_controller();
			Show* add_show(CueController* controller, Event* events, unsigned short num_events);
			Colors::RGB get_pixel_color(unsigned char section, unsigned int pixel);
			unsigned char get_num_sections();
			unsigned short get_refresh_interval();
			bool get_running();
			Section* get_section(unsigned char section);
			Show* get_show();
			void set_brightness(unsigned char brightness);
			void set_refresh_interval(unsigned short interval);
			void set_running(bool running);
			void set_sections(Section* sections, unsigned char num_sections);
			void update(const unsigned long& current_time);

		private:
			/// Sets the global brightness level from 0 - 255. Defaults to 255, or 100% brightness.
			unsigned char brightness_ = 255;

			CueController* cue_controller_ = nullptr;

			/// The time since the Pixels were last refreshed in milliseconds. Defaults to 0.
			unsigned long last_refresh_ = 0;

			/// Number of Sections managed by the Maestro.
			unsigned char num_sections_;

			/// The time between Section refreshes in milliseconds. Defaults to 20ms (50Hz).
			unsigned short refresh_interval_ = 20;

			/// Active running state of the Maestro.
			bool running_ = true;

			/// Sections managed by the Maestro.
			Section* sections_ = nullptr;

			/// Show managed by the Maestro.
			Show* show_ = nullptr;
	};
}

#endif
