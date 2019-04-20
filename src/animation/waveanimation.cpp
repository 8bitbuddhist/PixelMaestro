#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Wave;
		map();
	}

	int8_t WaveAnimation::get_skew() const {
		return skew_;
	}

	void WaveAnimation::set_skew(int8_t skew) {
		this->skew_ = skew;
		map();
	}

	// FIXME: Streak of black Pixels when skew_ is negative
	void WaveAnimation::map() {
		for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
			for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
				if (orientation_ == Orientation::Vertical) {
					set_map_color_index(x, y, y + (x * skew_));
				}
				else {	// Horizontal
					set_map_color_index(x, y, x + (y * skew_));
				}
			}
		}
	}

	void WaveAnimation::update() {
		update_cycle(0, palette_->get_num_colors());
	}
}
