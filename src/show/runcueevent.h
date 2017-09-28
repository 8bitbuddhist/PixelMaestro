#ifndef RUNCUEEVENT_H
#define RUNCUEEVENT_H

#include "../cue/cue.h"
#include "event.h"

namespace PixelMaestro {
	class RunCueEvent : public Event{
		public:
			RunCueEvent(unsigned long time, Maestro* maestro, unsigned char* buffer);
			~RunCueEvent();
			void run();

		private:
			unsigned char* cue_ = nullptr;
			Maestro* maestro_ = nullptr;
	};
}

#endif // RUNCUEEVENT_H
