#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Colors::RGB* colors, uint8_t num_colors) : Animation(colors, num_colors) {
		type_ = AnimationType::Random;
	}

	void RandomAnimation::update(Section* section) {
		for (uint32_t pixel = 0; pixel < section->get_dimensions()->size(); pixel++) {
			section->set_one(pixel, &colors_[Utility::rand(num_colors_)]);
		}
	}

	RandomAnimation::~RandomAnimation() {}
}
