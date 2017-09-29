/*
 * Event.h - Base class for Show events.
 */

#ifndef EVENT_H
#define EVENT_H

#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class CueController;
	class Maestro;
	class Event {

		public:
			Event(unsigned long time, const unsigned char* cue);
			~Event();
			unsigned long get_time();
			void run(CueController* controller);

		protected:
			/// The Cue to run.
			unsigned char* cue_;

			/// Time that this Event will run.
			unsigned long time_;

	};
}

#endif // EVENT_H
