#include "sectiontogglefadeevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	SectionToggleFadeEvent::SectionToggleFadeEvent(unsigned long time, Section* section) : Event(time) {
		this->section_ = section;
	}

	void SectionToggleFadeEvent::run() {
		section_->toggle_fade();
	}
}
