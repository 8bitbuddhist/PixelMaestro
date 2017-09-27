#ifndef RUNCOMMANDEVENT_H
#define RUNCOMMANDEVENT_H

#include "../command/command.h"
#include "event.h"

namespace PixelMaestro {
	class RunCommandEvent : public Event{
		public:
			RunCommandEvent(unsigned long time, Maestro* maestro, unsigned char* buffer);
			~RunCommandEvent();
			void run();

		private:
			unsigned char* buffer_;
			Maestro* maestro_ = nullptr;
	};
}

#endif // RUNCOMMANDEVENT_H
