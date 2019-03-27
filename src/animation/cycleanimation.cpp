#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Cycle;
	}

	void CycleAnimation::update() {
		for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
			for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
				section_.set_one(x, y, palette_->get_color_at_index(cycle_index_), timer_->get_step_count());
			}
		}
		update_cycle(0, palette_->get_num_colors());
	}
}
