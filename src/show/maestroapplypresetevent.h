#ifndef MAESTROAPPLYPRESETEVENT_H
#define MAESTROAPPLYPRESETEVENT_H

#include "../core/maestro.h"
#include "event.h"

namespace PixelMaestro {
	class MaestroApplyPresetEvent : public Event {
		public:
			MaestroApplyPresetEvent(unsigned long time, Maestro* maestro, Preset* preset);
			void run();

		private:
			Maestro* maestro_;
			Preset* preset_;
	};
}

#endif // MAESTROAPPLYPRESETEVENT_H
