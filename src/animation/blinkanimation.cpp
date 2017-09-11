#include "blinkanimation.h"

namespace PixelMaestro {
	BlinkAnimation::BlinkAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void BlinkAnimation::update() {
		// Alternate the Pixel between its normal color and off (Colors::BLACK).
		if (cycle_index_ == 0) {

			if (orientation_ == Orientations::VERTICAL) {
				for (unsigned short x = 0; x < section_->get_dimensions()->x; x++) {
					for (unsigned short y = 0; y < section_->get_dimensions()->y; y++) {
						section_->set_one(x, y, get_color_at_index(y));
					}
				}
			}
			else {	// Horizontal

				for (unsigned short y = 0; y < section_->get_dimensions()->y; y++) {
					for (unsigned short x = 0; x < section_->get_dimensions()->x; x++) {
						section_->set_one(x, y, get_color_at_index(x));
					}
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
