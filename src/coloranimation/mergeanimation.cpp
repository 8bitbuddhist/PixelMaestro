#include "mergeanimation.h"

namespace PixelMaestro {
	MergeAnimation::MergeAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : ColorAnimation(section, colors, num_colors) { }

	void MergeAnimation::update() {
		if (orientation_ == VERTICAL) {
			for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
				mid_point_ = (section_->get_dimensions()->y / 2) - 1;
				count_ = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int row = mid_point_; row >= 0; row--) {
					section_->set_one(row, column, get_color_at_index(count_ + cycle_index_));
					count_++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (section_->get_num_pixels() % 2 != 0) {
					mid_point_ += 1;
					section_->set_one(mid_point_, column, &colors_[cycle_index_]);
				}

				mid_point_ += 1;

				// Go from the center to the last
				count_ = 0;
				for (short row = mid_point_; row < section_->get_dimensions()->y; row++) {
					section_->set_one(row, column, get_color_at_index(count_ + cycle_index_));
					count_++;
				}
			}
		}
		else {	// Horizontal
			for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
				mid_point_ = (section_->get_dimensions()->x / 2) - 1;
				count_ = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int column = mid_point_; column >= 0; column--) {
					section_->set_one(row, column, get_color_at_index(count_ + cycle_index_));
					count_++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (section_->get_num_pixels() % 2 != 0) {
					mid_point_ += 1;
					section_->set_one(row, mid_point_, &colors_[cycle_index_]);
				}

				mid_point_ += 1;

				// Go from the center to the last
				count_ = 0;
				for (short column = mid_point_; column < section_->get_dimensions()->x; column++) {
					section_->set_one(row, column, get_color_at_index(count_ + cycle_index_));
					count_++;
				}
			}
		}

		update_cycle(0, num_colors_);
	}
}
