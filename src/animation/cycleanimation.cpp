#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Cycle;
	}

	void CycleAnimation::update() {
		section_->set_all(get_color_at_index(cycle_index_));
		update_cycle(0, num_colors_);
	}

	CycleAnimation::~CycleAnimation() {}
}
