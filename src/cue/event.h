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
			Event(uint32_t time, const uint8_t* cue);
			~Event();
			uint32_t get_time();
			void run(CueController* controller);

		protected:
			/// The Cue to run.
			uint8_t* cue_;

			/// Time that this Event will run.
			uint32_t time_;

	};
}

#endif // EVENT_H
