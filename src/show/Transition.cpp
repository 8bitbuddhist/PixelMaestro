#include "Transition.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	Transition::Transition(unsigned long time) {
		this->time_ = time;
	}

	unsigned long Transition::getTime() {
		return this->time_;
	}

	void Transition::setTime(unsigned long time) {
		this->time_ = time;
	}
}
