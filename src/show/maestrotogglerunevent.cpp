#include "maestrotogglerunevent.h"

namespace PixelMaestro {

	MaestroToggleRunEvent::MaestroToggleRunEvent(unsigned long time, Maestro *maestro) : Event(time) {
		this->maestro_ = maestro;
	}

	void MaestroToggleRunEvent::run() {
		this->maestro_->toggleRunning();
	}
}
