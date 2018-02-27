#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Wave;
	}

	bool WaveAnimation::get_merge() const {
		return merge_;
	}

	int8_t WaveAnimation::get_skew() const {
		return skew_;
	}

	void WaveAnimation::set_merge(bool merge) {
		this->merge_ = merge;
	}

	void WaveAnimation::set_skew(int8_t skew) {
		this->skew_ = skew;
	}

	void WaveAnimation::update() {
		if (merge_) {
			Point center = get_center();
			if (orientation_ == Orientation::Vertical) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					uint16_t count = 0;

					// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
					for (int32_t y = center.y; y >= 0; y--) {
						section_->set_one(x, y, get_color_at_index(count + cycle_index_ + (x * skew_)));
						count++;
					}

					/*
						Check for an odd number of Pixels.
						If so, set the center one to index 0.
					*/
					uint8_t offset = 0;
					if (section_->get_dimensions()->size() % 2 != 0) {
						offset += 1;
						section_->set_one(x, center.y + offset, get_color_at_index(cycle_index_ + (x * skew_)));
					}

					offset += 1;

					// Go from the center to the last
					count = 0;
					for (uint16_t y = center.y + offset; y < section_->get_dimensions()->y; y++) {
						section_->set_one(x, y, get_color_at_index(count + cycle_index_ + (x * skew_)));
						count++;
					}
				}
			}
			else {	// Horizontal
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					uint16_t count = 0;

					// Note: ROW MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
					for (int32_t x = center.x; x >= 0; x--) {
						section_->set_one(x, y, get_color_at_index(count + cycle_index_ + (y * skew_)));
						count++;
					}

					/*
						Check for an odd number of Pixels.
						If so, set the center one to index 0.
					*/
					uint8_t offset = 0;
					if (section_->get_dimensions()->size() % 2 != 0) {
						offset += 1;
						section_->set_one(center.x + offset, y, get_color_at_index(cycle_index_ + (y * skew_)));
					}

					offset += 1;

					// Go from the center to the last
					count = 0;
					for (uint16_t x = center.x + offset; x < section_->get_dimensions()->x; x++) {
						section_->set_one(x, y, get_color_at_index(count + cycle_index_ + (y * skew_)));
						count++;
					}
				}
			}
		}
		else {
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
		}

		update_cycle(0, num_colors_);
	}

	WaveAnimation::~WaveAnimation() {}
}
