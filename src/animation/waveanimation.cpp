#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section* section) : MappedAnimation(section) {
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

	void WaveAnimation::map() {
		for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				if (orientation_ == Orientation::Vertical) {
					map_[y][x] = y + (x * skew_);
				}
				else {	// Horizontal
					map_[y][x] = x + (y * skew_);
				}
			}
		}
	}

	void WaveAnimation::update() {
		MappedAnimation::update();

		// Rebuild map if the orientation changes.
		if (orientation_ != last_orientation_) {
			map();
			last_orientation_ = orientation_;
		}

		for (uint8_t x = 0; x < dimensions_.x; x++) {
			for (uint8_t y = 0; y < dimensions_.y; y++) {
				section_->set_one(x, y, palette_->get_color_at_index(map_[y][x] + cycle_index_), timer_->get_step_count());
			}
		}

		update_cycle(0, palette_->get_num_colors());
	}
}
