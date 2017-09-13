#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Colors::RGB* colors, unsigned short num_colors) : Animation(colors, num_colors) { }

	void RandomAnimation::update(Section* section) {
		for (unsigned int pixel = 0; pixel < section->get_dimensions()->size(); pixel++) {
			section->set_one(pixel, &colors_[Utility::rand() % num_colors_]);
		}
	}
}
