#ifndef TOGGLERUNEVENT_H
#define TOGGLERUNEVENT_H

#include "../maestro.h"
#include "event.h"

namespace PixelMaestro {
	class MaestroToggleRunEvent : public Event {

		public:
			MaestroToggleRunEvent(unsigned long time, Maestro *maestro);
			void run();

		private:
			Maestro *maestro_;
	};
}

#endif // TOGGLERUNEVENT_H
