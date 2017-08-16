#include "SectionSetOverlayEvent.h"

namespace PixelMaestro {
	SectionSetOverlayEvent::SectionSetOverlayEvent(unsigned long time, Section *section, Section::Overlay *overlay) : Event(time) {
		this->section_ = section;
		this->overlay_ = overlay;
	}

	SectionSetOverlayEvent::SectionSetOverlayEvent(unsigned long time, Section *section, Section *overlaySection, Colors::MixMode mixMode, float alpha) : Event(time) {
		this->section_ = section;
		this->overlay_ = new Section::Overlay(overlaySection, mixMode, alpha);
	}

	void SectionSetOverlayEvent::run() {
		this->section_->setOverlay(this->overlay_);
	}
}
