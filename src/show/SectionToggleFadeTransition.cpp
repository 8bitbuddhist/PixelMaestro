#include "SectionToggleFadeTransition.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	SectionToggleFadeTransition::SectionToggleFadeTransition(unsigned long time, Section *section) : Transition(time) {
		this->section_ = section;
	}

	void SectionToggleFadeTransition::run() {
		this->section_->toggleFade();
	}
}
