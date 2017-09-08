#include "solidanimation.h"

namespace PixelMaestro {
	SolidAnimation::SolidAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void SolidAnimation::update() {
		for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
			for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
				section_->set_one(row, column, get_color_at_index(column));
			}
		}
	}
}
