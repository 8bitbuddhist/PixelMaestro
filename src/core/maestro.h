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
			Maestro(Section* sections, uint8_t num_sections);
			~Maestro();
			CueController* add_cue_controller();
			Show* add_show(Event* events, uint16_t num_events);
			CueController* get_cue_controller();
			Colors::RGB get_pixel_color(uint8_t section, uint32_t pixel);
			uint8_t get_num_sections();
			uint16_t get_refresh_interval();
			bool get_running();
			Section* get_section(uint8_t section);
			Show* get_show();
			void set_brightness(uint8_t brightness);
			void set_refresh_interval(uint16_t interval);
			void set_running(bool running);
			void set_sections(Section* sections, uint8_t num_sections);
			void update(const uint32_t& current_time);

		private:
			/// Sets the global brightness level from 0 - 255. Defaults to 255, or 100% brightness.
			uint8_t brightness_ = 255;

			CueController* cue_controller_ = nullptr;

			/// The time since the Pixels were last refreshed in milliseconds. Defaults to 0.
			uint32_t last_refresh_ = 0;

			/// Number of Sections managed by the Maestro.
			uint8_t num_sections_;

			/// The time between Section refreshes in milliseconds. Defaults to 20ms (50Hz).
			uint16_t refresh_interval_ = 20;

			/// Active running state of the Maestro.
			bool running_ = true;

			/// Sections managed by the Maestro.
			Section* sections_ = nullptr;

			/// Show managed by the Maestro.
			Show* show_ = nullptr;
	};
}

#endif
