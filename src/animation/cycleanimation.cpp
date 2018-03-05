#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Cycle;
	}

	void CycleAnimation::update() {
		for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
			section_->set_one(pixel, palette_->get_color_at_index(cycle_index_));
		}
		update_cycle(0, palette_->get_size());
	}

	CycleAnimation::~CycleAnimation() {}
}
