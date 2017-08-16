#include "SectionSetOverlayEvent.h"

namespace PixelMaestro {
	SectionSetOverlayEvent::SectionSetOverlayEvent(unsigned long time, Section *section, Section *overlay, Colors::MixMode mixMode, float alpha) : Event(time) {
		this->section_ = section;
		this->overlay_ = overlay;
		this->mix_mode_ = mixMode;
		this->alpha_ = alpha;
	}

	void SectionSetOverlayEvent::run() {
		this->section_->setOverlay(this->overlay_, this->mix_mode_, this->alpha_);
	}
}
