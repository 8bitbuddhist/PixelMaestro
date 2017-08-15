#include "SectionSetOverlayTransition.h"

namespace PixelMaestro {
	SectionSetOverlayTransition::SectionSetOverlayTransition(unsigned long time, Section *section, Section *overlay, Colors::MixMode mixMode, float alpha) : Transition(time) {
		this->section_ = section;
		this->overlay_ = overlay;
		this->mix_mode_ = mixMode;
		this->alpha_ = alpha;
	}

	void SectionSetOverlayTransition::run() {
		this->section_->setOverlay(this->overlay_, this->mix_mode_, this->alpha_);
	}
}
