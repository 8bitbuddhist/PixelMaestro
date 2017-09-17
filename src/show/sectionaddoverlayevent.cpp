#include "sectionaddoverlayevent.h"

namespace PixelMaestro {
	SectionAddOverlayEvent::SectionAddOverlayEvent(unsigned long time, Section* section, Colors::MixMode mix_mode, unsigned char alpha) : Event(time) {
		this->section_ = section;
		this->mix_mode_ = mix_mode;
		this->alpha_ = alpha;
	}

	void SectionAddOverlayEvent::run() {
		section_->add_overlay(mix_mode_, alpha_);
	}
}
