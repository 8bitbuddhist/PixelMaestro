#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Cycle;
		map();
	}

	void CycleAnimation::map() {
		for (uint16_t x = 0; x < section_.get_dimensions().x; x++) {
			for (uint16_t y = 0; y < section_.get_dimensions().y; y++) {
				set_map_color_index(x, y, frame_index_);
			}
		}
	}

	void CycleAnimation::update() {
		update_frame(0, palette_->get_num_colors());
	}
}
