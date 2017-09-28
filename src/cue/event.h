/*
 * Event.h - Base class for Show events.
 */

#ifndef EVENT_H
#define EVENT_H

#include "../core/maestro.h"

namespace PixelMaestro {
	class Maestro;
	class Event {

		public:
			Event(unsigned long time, Maestro* maestro, const unsigned char* cue);
			~Event();
			unsigned long get_time();
			void run();

		protected:
			/// The Cue to run.
			unsigned char* cue_;

			/// The Maestro running the Cue.
			Maestro* maestro_;

			/// Time that this Event will run.
			unsigned long time_;

	};
}

#endif // EVENT_H
