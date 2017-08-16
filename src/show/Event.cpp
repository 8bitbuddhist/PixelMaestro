#include "Event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	Event::Event(unsigned long time) {
		this->time_ = time;
	}

	unsigned long Event::getTime() {
		return this->time_;
	}

	void Event::setTime(unsigned long time) {
		this->time_ = time;
	}
}
