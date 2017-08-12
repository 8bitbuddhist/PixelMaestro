#include "MaestroToggleRunTransition.h"

namespace PixelMaestro {

	MaestroToggleRunTransition::MaestroToggleRunTransition(Maestro *maestro, unsigned long time) : Transition(time) {
		this->maestro_ = maestro;
	}

	void MaestroToggleRunTransition::run() {
		this->maestro_->toggleRunning();
	}
}
