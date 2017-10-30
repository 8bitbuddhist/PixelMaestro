#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Colors::RGB* colors, uint8_t num_colors) : Animation(colors, num_colors) {
		type_ = AnimationType::Cycle;
	}

	void CycleAnimation::update(Section* section) {
		section->set_all(get_color_at_index(cycle_index_));
		update_cycle(0, num_colors_);
	}

	CycleAnimation::~CycleAnimation() {}
}
