#include "solidanimation.h"

namespace PixelMaestro {
	SolidAnimation::SolidAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Solid;
		map();
	}

	void SolidAnimation::map() {
		if (orientation_ == Orientation::Vertical) {
			for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
				for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
					set_map_color_index(x, y, y);
				}
			}
		}
		else {	// Horizontal
			for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
					set_map_color_index(x, y, x);
				}
			}
		}
	}
}
