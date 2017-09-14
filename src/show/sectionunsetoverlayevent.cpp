#include "sectionunsetoverlayevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Removes an Overlay from a Section.
	 * @param time Time until the Event runs.
	 * @param section Section to modify.
	 */
	SectionUnsetOverlayEvent::SectionUnsetOverlayEvent(unsigned long time, Section* section) : Event(time) {
		this->section_ = section;
	}

	void SectionUnsetOverlayEvent::run() {
		// TODO: Delete meh
		//section_->unset_overlay();
	}
}
