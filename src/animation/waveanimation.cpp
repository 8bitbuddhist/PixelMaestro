#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Wave;
	}

	int8_t WaveAnimation::get_skew() {
		return skew_;
	}

	void WaveAnimation::set_skew(int8_t skew) {
		this->skew_ = skew;
	}

	void WaveAnimation::update() {
		for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				if (orientation_ == Orientation::Vertical) {
					section_->set_one(x, y, get_color_at_index(y + cycle_index_ + (x * skew_)));
				}
				else {	// Horizontal
					section_->set_one(x, y, get_color_at_index(x + cycle_index_ + (y * skew_)));
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	WaveAnimation::~WaveAnimation() {}
}
