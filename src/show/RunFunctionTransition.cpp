#include "RunFunctionTransition.h"

namespace PixelMaestro {
	RunFunctionTransition::RunFunctionTransition(unsigned long time, function<void()> action) : Transition(time) {
		this->action_ = action;
	}

	void RunFunctionTransition::run() {
		this->action_();
	}
}
