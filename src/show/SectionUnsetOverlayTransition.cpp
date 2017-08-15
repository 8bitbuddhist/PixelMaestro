#include "SectionUnsetOverlayTransition.h"

namespace PixelMaestro {
	SectionUnsetOverlayTransition::SectionUnsetOverlayTransition(unsigned long time, Section *section) : Transition(time) {
		this->section_ = section;
	}

	void SectionUnsetOverlayTransition::run() {
		this->section_->unsetOverlay();
	}
}
