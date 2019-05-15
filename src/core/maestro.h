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
#include "timer/timer.h"

namespace PixelMaestro {
	class CueController;
	class Event;
	class Show;
	class Maestro {

		public:
			Maestro(uint16_t rows, uint16_t columns, uint8_t num_sections = 1);
			Maestro(Section* sections, uint8_t num_sections);
			~Maestro();
			CueController& get_cue_controller() const;
			Colors::RGB get_pixel_color(uint8_t section, uint16_t x, uint16_t y) const;
			uint8_t get_num_sections() const;
			Section& get_section(uint8_t section) const;
			Show* get_show() const;
			Timer& get_timer() const;
			void remove_sections();
			void remove_show();
			void set_brightness(uint8_t brightness);
			CueController& set_cue_controller(uint16_t buffer_size = UINT8_MAX);
			void set_sections(Section* sections, uint8_t num_sections);
			Timer& set_timer(uint16_t interval);
			Show& set_show(Event* events, uint16_t num_events);
			void sync(const uint32_t& new_time = 0);
			bool update(const uint32_t& current_time, bool force = false);

		private:
			/// Controller object for reading and executing Cues.
			CueController* cue_controller_ = nullptr;

			/// Tracks whether the Sections were allocated by the user or by the Maestro.
			bool dynamically_allocated_sections_ = false;

			/// Number of Sections managed by the Maestro.
			uint8_t num_sections_ = 0;

			/// Sections managed by the Maestro.
			Section* sections_ = nullptr;

			/// Show managed by the Maestro.
			Show* show_ = nullptr;

			/// The time between refreshes in milliseconds. Defaults to 50ms (20 refreshes per second).
			Timer timer_ = Timer(50);
	};
}

#endif
