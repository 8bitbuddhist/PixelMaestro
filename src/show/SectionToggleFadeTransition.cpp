#include "SectionToggleFadeTransition.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	SectionToggleFadeTransition::SectionToggleFadeTransition(Section *section, unsigned long time) : Transition(time) {
			this->section_ = section;
	}

	void SectionToggleFadeTransition::run() {
		this->section_->toggleFade();
	}
}
