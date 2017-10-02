#include "blinkanimation.h"

namespace PixelMaestro {
	BlinkAnimation::BlinkAnimation(Colors::RGB* colors, uint8_t num_colors, uint16_t speed, uint16_t pause) : Animation(colors, num_colors, speed, pause) {
		type_ = Animation::Type::Blink;
	}

	void BlinkAnimation::update(Section* section) {
		// Alternate the Pixel between its normal color and off (Colors::BLACK).
		if (cycle_index_ == 0) {

			if (orientation_ == Orientation::Vertical) {
				for (uint16_t x = 0; x < section->get_dimensions()->x; x++) {
					for (uint16_t y = 0; y < section->get_dimensions()->y; y++) {
						section->set_one(x, y, get_color_at_index(y));
					}
				}
			}
			else {	// Horizontal

				for (uint16_t y = 0; y < section->get_dimensions()->y; y++) {
					for (uint16_t x = 0; x < section->get_dimensions()->x; x++) {
						section->set_one(x, y, get_color_at_index(x));
					}
				}
			}
		}
		else {
			section->set_all(&Colors::BLACK);
		}

		// Only run for two cycles.
		update_cycle(0, 2);
	}

	BlinkAnimation::~BlinkAnimation() {}
}
