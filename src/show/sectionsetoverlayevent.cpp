#include "sectionsetoverlayevent.h"

namespace PixelMaestro {
	SectionSetOverlayEvent::SectionSetOverlayEvent(unsigned long time, Section* section, Section::Overlay* overlay) : Event(time) {
		this->section_ = section;
		this->overlay_ = overlay;
	}

	SectionSetOverlayEvent::SectionSetOverlayEvent(unsigned long time, Section* section, Section* overlay_section, Colors::MixMode mix_mode, float alpha) : Event(time) {
		this->section_ = section;
		this->overlay_ = new Section::Overlay(overlay_section, mix_mode, alpha);
	}

	void SectionSetOverlayEvent::run() {
		section_->set_overlay(overlay_);
	}
}
