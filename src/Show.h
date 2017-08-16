/*
	Show.cpp - Library for scheduling PixelMaestro animations.
*/

#ifndef SHOW_H
#define SHOW_H

#include "show/Event.h"
#include "Maestro.h"

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

			Show();
			Show (Maestro *maestro);
			unsigned short getCurrentIndex();
			bool getLooping();
			Maestro *getMaestro();
			void setMaestro(Maestro *maestro);
			void setTiming(TimingModes timing);
			void setEvents(Event **events, unsigned char numEvents);
			void toggleLooping();
			void update(const unsigned long &currentTime);

		private:
			/// The index of the current Event.
			unsigned short current_index_ = 0;

			/// The index of the last run Event.
			unsigned short last_index_ = 0;

			/// The time that the last Event ran.
			unsigned long last_time_ = 0;

			/// Whether to loop over the Event.
			bool loop_ = false;

			/// The Maestro that the Events apply to.
			Maestro *maestro_ = nullptr;

			/// The number of Events in the array.
			unsigned char num_events_;

			/// Method for measuring a Event's start time. Defaults to Absolute.
			TimingModes timing_ = TimingModes::ABSOLUTE;

			/// Events used in the Show.
			Event **events_;

			unsigned short getNextIndex();
	};
}

#endif // SHOW_H
