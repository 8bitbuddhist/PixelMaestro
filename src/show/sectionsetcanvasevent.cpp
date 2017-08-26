#include "sectionsetcanvasevent.h"

namespace PixelMaestro {
	SectionSetCanvasEvent::SectionSetCanvasEvent(unsigned long time, Section* section, Canvas* canvas) : Event(time) {
		this->section_ = section;
		this->canvas_ = canvas;
	}

	void SectionSetCanvasEvent::run() {
		this->section_->set_canvas(this->canvas_);
	}
}
