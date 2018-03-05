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
						section_->set_one(x, y, palette_->get_color_at_index(y));
					}
				}
			}
			else {	// Horizontal
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
						section_->set_one(x, y, palette_->get_color_at_index(x));
					}
				}
			}
		}
		else {
			for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
				section_->set_one(pixel, &black_);
			}
		}

		// Only run for two cycles.
		update_cycle(0, 2);
	}

	BlinkAnimation::~BlinkAnimation() {}
}
