#include <math.h>
#include "plasmaanimation.h"

namespace PixelMaestro {
	PlasmaAnimation::PlasmaAnimation(Colors::RGB* colors, unsigned short num_colors, float size, float resolution) : Animation(colors, num_colors) {
		size_ = size;
		resolution_ = resolution;
	}

	void PlasmaAnimation::update(Section* section) {
		int color_index;
		for (unsigned short y = 0; y < section->get_dimensions()->y; y++) {
			for (unsigned short x = 0; x < section->get_dimensions()->x; x++) {
				color_index = ((size_ + (size_ * sin(x / resolution_))) + (size_ + (size_ * sin(y / resolution_)))) / 2;
				section->set_one(x, y, get_color_at_index(color_index + cycle_index_));
			}
		}

		update_cycle(0, num_colors_);
	}
}
