#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section* section, bool reverse, Orientations orientation) : ColorAnimation(section, reverse, orientation) { }

	void WaveAnimation::update() {
		for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
			for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
				if (orientation_ == VERTICAL) {
					section_->set_one(row, column, &colors_[get_color_index(row + cycle_index_)]);
				}
				else {	// Horizontal
					section_->set_one(row, column, &colors_[get_color_index(column + cycle_index_)]);
				}
			}
		}

		update_cycle(0, num_colors_);
	}
}
