/*
	Show.cpp - Library for scheduling PixelMaestro animations.
*/

#ifndef SHOW_H
#define SHOW_H

#include <functional>
#include "Maestro.h"

using namespace std;
using namespace PixelMaestro;

namespace PixelMaestro {
	class Show {
		public:

			/// Defines an action that a Maestro will perform at a specific time.
			struct Transition {

				/// How long until the action will be performed.
				unsigned long time;

				/// The function to call when the Transition triggers.
				function<void()> action;
			};

			/// The method used to measure time between Transitions.
			enum TimingModes {

				/// Counts time from when the Show starts.
				ABSOLUTE,

				/// Counts time since the last Transition.
				RELATIVE
			};

			unsigned short getCurrentIndex();
			bool getLooping();
			Maestro *getMaestro();
			void setMaestro(Maestro *maestro);
			void setTiming(TimingModes timing);
			void setTransitions(Transition *transitions, unsigned char numTransitions);
			void toggleLooping();
			void update(const unsigned long &currentTime);

		private:
			/// The index of the current Transition.
			unsigned short current_index_ = 0;

			/// The index of the last run Transition.
			unsigned short last_index_ = 0;

			/// The time that the last Transition ran.
			unsigned long last_time_ = 0;

			/// Whether to loop over the Transition.
			bool loop_ = false;

			/// The Maestro that the Transitions apply to.
			Maestro *maestro_;

			/// The number of Transitions in the array.
			unsigned char num_transitions_;

			/// Method for measuring a Transition's start time. Defaults to Absolute.
			TimingModes timing_ = TimingModes::ABSOLUTE;

			/// Transitions used in the Show.
			Transition *transitions_;

			unsigned short getNextIndex();
	};
}

#endif // SHOW_H
