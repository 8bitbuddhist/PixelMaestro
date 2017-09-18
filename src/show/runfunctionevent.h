#ifdef __STDC_HOSTED__

#ifndef RUNFUNCTIONEVENT_H
#define RUNFUNCTIONEVENT_H

#include "event.h"
#include <functional>

namespace PixelMaestro {
	class RunFunctionEvent : public Event {
		public:
			RunFunctionEvent(unsigned long time, std::function<void()> callable);
			void run();

		private:
			std::function<void()> callable_;
	};
}

#endif // RUNFUNCTIONEVENT_H

#endif // __STDC_HOSTED__
