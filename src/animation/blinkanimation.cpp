#include "blinkanimation.h"

namespace PixelMaestro {
	BlinkAnimation::BlinkAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Blink;
	}

	void BlinkAnimation::update() {
		// Alternate the Pixel between its normal color and off.
		if (cycle_index_ == 0) {
			if (orientation_ == Orientation::Vertical) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
						section_->set_one(x, y, palette_->get_color_at_index(y), timer_->get_step_count());
					}
				}
			}
			else {	// Horizontal
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
						section_->set_one(x, y, palette_->get_color_at_index(x), timer_->get_step_count());
					}
				}
			}
		}
		else {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					section_->set_one(x, y, &black_, timer_->get_step_count());
				}
			}
		}

		// Only run for two cycles.
		update_cycle(0, 2);
	}
}
