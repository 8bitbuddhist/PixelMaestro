#include "waveanimation.h"

namespace PixelMaestro {
	/*
	 * TODO: Add ability to change the starting point for each row.
	 * Considered adding a `skew` parameter, which sets the offset of the bottom row from the top (or left from right if vertically oriented).
	 */
	WaveAnimation::WaveAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Wave;
	}

	void WaveAnimation::update() {
		for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				if (orientation_ == Vertical) {
					section_->set_one(x, y, get_color_at_index(y + cycle_index_));
				}
				else {	// Horizontal
					section_->set_one(x, y, get_color_at_index(x + cycle_index_));
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	WaveAnimation::~WaveAnimation() {}
}
