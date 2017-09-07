#include "sectiontogglefadeevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	// TODO: Rename this Event (and Events like it) to ColorAnimation
	SectionToggleFadeEvent::SectionToggleFadeEvent(unsigned long time, Section* section) : Event(time) {
		this->section_ = section;
	}

	void SectionToggleFadeEvent::run() {
		section_->get_color_animation()->set_fade(!section_->get_color_animation()->get_fade());
	}
}
