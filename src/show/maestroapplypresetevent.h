#ifndef MAESTROAPPLYPRESETEVENT_H
#define MAESTROAPPLYPRESETEVENT_H

#include "../core/maestro.h"
#include "event.h"

namespace PixelMaestro {
	class MaestroApplyPresetEvent : public Event {
		public:
			MaestroApplyPresetEvent(unsigned long time, Maestro* maestro, Preset* preset, bool delete_preset_ = false);
			void run();

		private:
			bool delete_preset_;
			Maestro* maestro_;
			Preset* preset_;
	};
}

#endif // MAESTROAPPLYPRESETEVENT_H
