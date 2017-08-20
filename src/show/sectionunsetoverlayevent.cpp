#include "sectionunsetoverlayevent.h"

namespace PixelMaestro {
	SectionUnsetOverlayEvent::SectionUnsetOverlayEvent(unsigned long time, Section *section) : Event(time) {
		this->section_ = section;
	}

	void SectionUnsetOverlayEvent::run() {
		this->section_->unsetOverlay();
	}
}
