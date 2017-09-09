#include "maestrotogglerunevent.h"

namespace PixelMaestro {

	/**
	 * Constructor. Toggles the running state of a Maestro.
	 * @param time Time until the Event runs.
	 * @param maestro Maestro to toggle.
	 */
	MaestroToggleRunEvent::MaestroToggleRunEvent(unsigned long time, Maestro* maestro) : Event(time) {
		this->maestro_ = maestro;
	}

	void MaestroToggleRunEvent::run() {
		this->maestro_->toggle_running();
	}
}
