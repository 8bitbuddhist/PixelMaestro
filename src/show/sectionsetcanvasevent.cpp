#include "sectionsetcanvasevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Sets a Canvas to a Section.
	 * @param time Time until the Event runs.
	 * @param section Section to modify.
	 * @param canvas Canvas to apply.
	 */
	SectionSetCanvasEvent::SectionSetCanvasEvent(unsigned long time, Section* section, Canvas* canvas) : Event(time) {
		this->section_ = section;
		this->canvas_ = canvas;
	}

	void SectionSetCanvasEvent::run() {
		this->section_->set_canvas(this->canvas_);
	}
}
