#include "../utility.h"
#include "radialanimation.h"

namespace PixelMaestro {
	RadialAnimation::RadialAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void RadialAnimation::update() {
		// Check if the size of the grid has changed.
		if (size != *section_->get_dimensions()) {
			size = *section_->get_dimensions();
			center_ = {
				(short)(size.x / 2),
				(short)(size.y / 2)
			};
		}

		// For each Pixel, calculate its distance from the center of the grid, then use the distance to choose the index of the correct color.
		for (unsigned short x = 0; x < size.x; x++) {
			x_squared = Utility::square(x - center_.x);
			for (unsigned short y = 0; y < size.y; y++) {
				y_squared = Utility::square(y - center_.y);
				distance_ = Utility::sqrt(x_squared + y_squared);

				section_->set_one(x, y, get_color_at_index(distance_ + cycle_index_));
			}
		}

		update_cycle(0, num_colors_);
	}
}
