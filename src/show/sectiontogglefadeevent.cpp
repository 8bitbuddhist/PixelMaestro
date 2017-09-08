#include "sectiontogglefadeevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	// TODO: Move this Event (and Events like it) from Section to Animation
	SectionToggleFadeEvent::SectionToggleFadeEvent(unsigned long time, Section* section) : Event(time) {
		this->section_ = section;
	}

	void SectionToggleFadeEvent::run() {
		section_->get_color_animation()->set_fade(!section_->get_color_animation()->get_fade());
	}
}
