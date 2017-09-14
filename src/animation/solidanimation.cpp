#include "solidanimation.h"

namespace PixelMaestro {
	SolidAnimation::SolidAnimation(Colors::RGB* colors, unsigned char num_colors) : Animation(colors, num_colors) { }

	void SolidAnimation::update(Section* section) {
		if (orientation_ == Orientations::VERTICAL) {
			for (unsigned short x = 0; x < section->get_dimensions()->x; x++) {
				for (unsigned short y = 0; y < section->get_dimensions()->y; y++) {
					section->set_one(x, y, get_color_at_index(y));
				}
			}
		}
		else {	// Horizontal
			for (unsigned short y = 0; y < section->get_dimensions()->y; y++) {
				for (unsigned short x = 0; x < section->get_dimensions()->x; x++) {
					section->set_one(x, y, get_color_at_index(x));
				}
			}
		}
	}
}
