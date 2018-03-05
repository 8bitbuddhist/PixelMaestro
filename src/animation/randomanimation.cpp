#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Random;
	}

	void RandomAnimation::update() {
		for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
			section_->set_one(pixel, palette_->get_color_at_index(Utility::rand(palette_->get_size())));
		}
	}

	RandomAnimation::~RandomAnimation() {}
}
