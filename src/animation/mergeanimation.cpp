#include "mergeanimation.h"

namespace PixelMaestro {
	MergeAnimation::MergeAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Merge;
	}

	int8_t MergeAnimation::get_skew() {
		return skew_;
	}

	void MergeAnimation::set_skew(int8_t skew) {
		this->skew_ = skew;
	}

	void MergeAnimation::update() {
		Point center = get_center();
		if (orientation_ == Orientation::Vertical) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				count_ = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (int32_t y = center.y; y >= 0; y--) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_ + (x * skew_)));
					count_++;
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
				count_ = 0;
				for (uint16_t y = center.y + offset; y < section_->get_dimensions()->y; y++) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_ + (x * skew_)));
					count_++;
				}
			}
		}
		else {	// Horizontal
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				count_ = 0;

				// Note: ROW MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (int32_t x = center.x; x >= 0; x--) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_ + (y * skew_)));
					count_++;
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
				count_ = 0;
				for (uint16_t x = center.x + offset; x < section_->get_dimensions()->x; x++) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_ + (y * skew_)));
					count_++;
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	MergeAnimation::~MergeAnimation() {}
}
