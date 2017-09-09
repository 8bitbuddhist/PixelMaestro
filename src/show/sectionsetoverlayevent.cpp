#include "sectionsetoverlayevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Applies an Overlay to a Section.
	 * @param time Time until the Event runs.
	 * @param section Section to modify.
	 * @param overlay Overlay to apply.
	 */
	SectionSetOverlayEvent::SectionSetOverlayEvent(unsigned long time, Section* section, Section::Overlay* overlay) : Event(time) {
		this->section_ = section;
		this->overlay_ = overlay;
	}

	void SectionSetOverlayEvent::run() {
		section_->set_overlay(overlay_);
	}
}
