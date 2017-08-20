#include "sectionsetpatternevent.h"

namespace PixelMaestro {
	SectionSetPatternEvent::SectionSetPatternEvent(unsigned long time, Section *section, Section::Pattern *pattern) : Event(time) {
		this->section_ = section;
		this->pattern_ = pattern;
	}

	void SectionSetPatternEvent::run() {
		this->section_->setPattern(this->pattern_);
	}
}
