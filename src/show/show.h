/*
	Show.cpp - Library for scheduling PixelMaestro animations.
*/

#ifndef SHOW_H
#define SHOW_H

#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class Show {
		public:
			/// The method used to measure time between Events.
			enum TimingModes {

				/// Counts time from when the Show starts.
				ABSOLUTE,

				/// Counts time since the last Event.
				RELATIVE
			};

			Show(Event **events, unsigned short num_events);
			bool get_looping();
			TimingModes get_timing();
			void set_events(Event **events, unsigned short num_events);
			void set_timing(TimingModes timing);
			void set_looping(bool loop);
			void update(const unsigned long& current_time);

		private:
			/// The index of the current Event.
			unsigned short current_index_ = 0;

			/// Events used in the Show.
			Event **events_;

			/// The time that the last Event ran.
			unsigned long last_time_ = 0;

			/// Whether to loop over the Event.
			bool loop_ = false;

			/// The number of Events in the Show.
			unsigned short num_events_;

			/// Method for measuring a Event's start time. Defaults to Absolute.
			TimingModes timing_ = TimingModes::ABSOLUTE;

			void update_event_index();
	};
}

#endif // SHOW_H
