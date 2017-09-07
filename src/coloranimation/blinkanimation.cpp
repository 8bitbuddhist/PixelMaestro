#include "blinkanimation.h"

namespace PixelMaestro {
	BlinkAnimation::BlinkAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : ColorAnimation(section, colors, num_colors) { }

	void BlinkAnimation::update() {
		// Alternate the Pixel between its normal color and off (Colors::BLACK).
		if (cycle_index_ == 0) {
			for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
				for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
					section_->set_one(row, column, get_color_at_index(column));
				}
			}
		}
		else {
			section_->set_all(&Colors::BLACK);
		}

		// Only run for two cycles.
		update_cycle(0, 2);
	}
}
