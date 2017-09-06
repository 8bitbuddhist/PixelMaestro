#ifdef __STDC_HOSTED__

#include <functional>
#include "runfunctionevent.h"

namespace PixelMaestro {
	RunFunctionEvent::RunFunctionEvent(unsigned long time, std::function<void()> callable) : Event(time) {
		this->callable_ = callable;
	}

	void RunFunctionEvent::run() {
		callable_();
	}
}

#endif //__STDC_HOSTED__
