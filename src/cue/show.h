/*
	Show.cpp - Library for scheduling PixelMaestro Events.
*/

#ifndef SHOW_H
#define SHOW_H

#include <stdint.h>
#include "cuecontroller.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class CueController;
	class Show {
		public:
			/// The method used to measure time between Events.
			enum class TimingMode : uint8_t {

				/// Counts time since the start of the Show.
				Absolute,

				/// Counts time since the last Event.
				Relative
			};

			Show(CueController* controller, Event *events, uint16_t num_events);
			uint16_t get_current_index() const;
			Event* get_events() const;
			uint32_t get_last_time() const;
			bool get_looping() const;
			uint16_t get_num_events() const;
			TimingMode get_timing() const;
			void set_events(Event* events, uint16_t num_events, bool preserve_current_index = true);
			void set_timing(TimingMode timing);
			void set_looping(bool loop);
			void update(const uint32_t& current_time);

		private:
			/// The controller for running Cues.
			CueController* cue_controller_ = nullptr;

			/// The index of the current Event.
			uint16_t current_index_ = 0;

			/// Events used in the Show.
			Event* events_ = nullptr;

			/**
			 * The time that the last Event ran.
			 * We don't use Timing.h because we don't need to track an interval.
			 */
			uint32_t last_time_ = 0;

			/// Whether to loop over the Event list.
			bool loop_ = false;

			/// The number of Events in the Show.
			uint16_t num_events_;

			/// Method for measuring a Event's start time. Defaults to Absolute.
			TimingMode timing_ = TimingMode::Absolute;

			void check_next_event(const uint32_t& current_time);
			void update_event_index();
	};
}

#endif // SHOW_H
