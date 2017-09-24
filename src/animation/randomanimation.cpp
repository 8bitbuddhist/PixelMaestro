#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Colors::RGB* colors, unsigned char num_colors, unsigned short speed, unsigned short pause) : Animation(colors, num_colors, speed, pause) { }

	void RandomAnimation::update(Section* section) {
		for (unsigned int pixel = 0; pixel < section->get_dimensions()->size(); pixel++) {
			section->set_one(pixel, &colors_[Utility::rand(num_colors_)]);
		}
	}

	RandomAnimation::~RandomAnimation() {}
}
