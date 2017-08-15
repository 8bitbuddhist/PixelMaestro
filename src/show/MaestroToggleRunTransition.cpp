#include "MaestroToggleRunTransition.h"

namespace PixelMaestro {

	MaestroToggleRunTransition::MaestroToggleRunTransition(unsigned long time, Maestro *maestro) : Transition(time) {
		this->maestro_ = maestro;
	}

	void MaestroToggleRunTransition::run() {
		this->maestro_->toggleRunning();
	}
}
