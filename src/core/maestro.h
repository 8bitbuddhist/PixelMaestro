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
#include "timing/timing.h"

namespace PixelMaestro {
	class CueController;
	class Event;
	class Show;
	class Maestro {

		public:
			Maestro(uint16_t rows, uint16_t columns);
			Maestro(Section* sections, uint8_t num_sections);
			~Maestro();
			CueController* get_cue_controller();
			Colors::RGB get_pixel_color(uint8_t section, uint16_t x, uint16_t y);
			uint8_t get_num_sections();
			Section* get_section(uint8_t section);
			Show* get_show();
			Timing* get_timing();
			void set_brightness(uint8_t brightness);
			CueController* set_cue_controller();
			void set_running(bool running);
			void set_sections(Section* sections, uint8_t num_sections);
			Timing* set_timing(uint16_t interval);
			Show* set_show(Event* events, uint16_t num_events);
			void update(const uint32_t& current_time, bool force = false);

		private:
			/// Sets the global brightness level from 0 - 255. Defaults to 255, or 100% brightness.
			uint8_t brightness_ = 255;

			/// Controller object for reading and executing Cues.
			CueController* cue_controller_ = nullptr;

			/// Number of Sections managed by the Maestro.
			uint8_t num_sections_ = 0;

			/// Sections managed by the Maestro.
			Section* sections_ = nullptr;

			/// Show managed by the Maestro.
			Show* show_ = nullptr;

			/// The time between Section refreshes in milliseconds. Defaults to 20ms (50Hz).
			Timing timing_ = Timing(20);
	};
}

#endif
