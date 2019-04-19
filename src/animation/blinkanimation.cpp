#include "blinkanimation.h"

namespace PixelMaestro {
	BlinkAnimation::BlinkAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Blink;
		map();
	}

	void BlinkAnimation::map() {
		// Alternate the Pixel between its normal color and off.
		if (cycle_index_ == 0) {
			if (orientation_ == Orientation::Vertical) {
				for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
					for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
						set_pixel_map(x, y, y);
					}
				}
			}
			else {	// Horizontal
				for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
					for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
						set_pixel_map(x, y, x);
					}
				}
			}
		}
		else {
			for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
				for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
					set_pixel_map(x, y, 255);
				}
			}
		}
	}

	void BlinkAnimation::update() {
		update_cycle(0, 2);
	}
}
