#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Random;
		map();
	}

	void RandomAnimation::map() {
		if (palette_ == nullptr) return;

		for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
			for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
				set_pixel_map(x, y, Utility::rand(palette_->get_num_colors()));
			}
		}
	}
}
