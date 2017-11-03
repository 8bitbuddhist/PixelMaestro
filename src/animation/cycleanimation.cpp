#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Cycle;
	}

	void CycleAnimation::update() {
		for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
			section_->set_one(pixel, get_color_at_index(cycle_index_));
		}
		update_cycle(0, num_colors_);
	}

	CycleAnimation::~CycleAnimation() {}
}
