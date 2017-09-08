#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void WaveAnimation::update() {
		for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
			for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
				if (orientation_ == VERTICAL) {
					section_->set_one(row, column, get_color_at_index(row + cycle_index_));
				}
				else {	// Horizontal
					section_->set_one(row, column, get_color_at_index(column + cycle_index_));
				}
			}
		}

		update_cycle(0, num_colors_);
	}
}
