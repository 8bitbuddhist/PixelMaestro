#include "sectionremoveoverlayevent.h"

namespace PixelMaestro {
	SectionRemoveOverlayEvent::SectionRemoveOverlayEvent(unsigned long time, Section* section) : Event(time) {
		this->section_ = section;
	}

	void SectionRemoveOverlayEvent::run() {
		section_->remove_canvas();
	}
}
