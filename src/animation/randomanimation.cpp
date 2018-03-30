#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Random;
	}

	void RandomAnimation::update() {
		for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				section_->set_one(x, y, palette_->get_color_at_index(Utility::rand(palette_->get_size())));
			}
		}
	}

	RandomAnimation::~RandomAnimation() {}
}
