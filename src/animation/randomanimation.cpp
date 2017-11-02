#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Random;
	}

	void RandomAnimation::update() {
		for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
			section_->set_one(pixel, get_color_at_index(Utility::rand(num_colors_)));
		}
	}

	RandomAnimation::~RandomAnimation() {}
}
