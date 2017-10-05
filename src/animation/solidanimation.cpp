#include "solidanimation.h"

namespace PixelMaestro {
	SolidAnimation::SolidAnimation(Colors::RGB* colors, uint8_t num_colors, uint16_t speed, uint16_t pause) : Animation(colors, num_colors, speed, pause) {
		type_ = AnimationType::Solid;
	}

	void SolidAnimation::update(Section* section) {
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

	SolidAnimation::~SolidAnimation() {}
}
