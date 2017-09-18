#include "maestrosetrunningevent.h"

namespace PixelMaestro {

	/**
	 * Constructor. Toggles the running state of a Maestro.
	 * @param time Time until the Event runs.
	 * @param maestro Maestro to toggle.
	 * @param running Whether the Maestro is running or not.
	 */
	MaestroSetRunningEvent::MaestroSetRunningEvent(unsigned long time, Maestro* maestro, bool running) : Event(time) {
		this->maestro_ = maestro;
		this->running_ = running;
	}

	void MaestroSetRunningEvent::run() {
		this->maestro_->set_running(running_);
	}
}
