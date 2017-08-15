#include "SectionSetPatternTransition.h"

namespace PixelMaestro {
	SectionSetPatternTransition::SectionSetPatternTransition(unsigned long time, Section *section, Section::Pattern *pattern) : Transition(time) {
		this->section_ = section;
		this->pattern_ = pattern;
	}

	void SectionSetPatternTransition::run() {
		this->section_->setPattern(this->pattern_);
	}
}
