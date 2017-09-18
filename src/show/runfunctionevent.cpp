#ifdef __STDC_HOSTED__

#include <functional>
#include "runfunctionevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Runs a function.
	 * @param time Time until the Event runs.
	 * @param callable Function to call.
	 */
	RunFunctionEvent::RunFunctionEvent(unsigned long time, std::function<void()> callable) : Event(time) {
		this->callable_ = callable;
	}

	void RunFunctionEvent::run() {
		callable_();
	}
}

#endif //__STDC_HOSTED__
