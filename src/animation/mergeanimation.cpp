#include "mergeanimation.h"

namespace PixelMaestro {
	MergeAnimation::MergeAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void MergeAnimation::update() {
		if (orientation_ == VERTICAL) {
			for (unsigned short x = 0; x < section_->get_dimensions()->x; x++) {
				mid_point_ = (section_->get_dimensions()->y / 2) - 1;
				count_ = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int y = mid_point_; y >= 0; y--) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (section_->get_num_pixels() % 2 != 0) {
					mid_point_ += 1;
					section_->set_one(x, mid_point_, &colors_[cycle_index_]);
				}

				mid_point_ += 1;

				// Go from the center to the last
				count_ = 0;
				for (short y = mid_point_; y < section_->get_dimensions()->y; y++) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}
			}
		}
		else {	// Horizontal
			for (unsigned short y = 0; y < section_->get_dimensions()->y; y++) {
				mid_point_ = (section_->get_dimensions()->x / 2) - 1;
				count_ = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int x = mid_point_; x >= 0; x--) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (section_->get_num_pixels() % 2 != 0) {
					mid_point_ += 1;
					section_->set_one(mid_point_, y, &colors_[cycle_index_]);
				}

				mid_point_ += 1;

				// Go from the center to the last
				count_ = 0;
				for (short x = mid_point_; x < section_->get_dimensions()->x; x++) {
					section_->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}
			}
		}

		update_cycle(0, num_colors_);
	}
}
