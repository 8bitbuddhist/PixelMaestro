#ifndef MAESTROSETRUNNINGEVENT_H
#define MAESTROSETRUNNINGEVENT_H

#include "../core/maestro.h"
#include "event.h"

namespace PixelMaestro {
	class MaestroSetRunningEvent : public Event {

		public:
			MaestroSetRunningEvent(unsigned long time, Maestro* maestro, bool running);
			void run();

		private:
			Maestro* maestro_;
			bool running_;
	};
}

#endif // MAESTROSETRUNNINGEVENT_H
