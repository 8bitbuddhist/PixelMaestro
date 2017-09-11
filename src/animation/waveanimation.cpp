#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void WaveAnimation::update() {
		for (unsigned short y = 0; y < section_->get_dimensions()->y; y++) {
			for (unsigned short x = 0; x < section_->get_dimensions()->x; x++) {
				if (orientation_ == VERTICAL) {
					section_->set_one(x, y, get_color_at_index(y + cycle_index_));
				}
				else {	// Horizontal
					section_->set_one(x, y, get_color_at_index(x + cycle_index_));
				}
			}
		}

		update_cycle(0, num_colors_);
	}
}
