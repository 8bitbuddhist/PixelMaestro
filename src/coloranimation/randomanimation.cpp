#include "randomanimation.h"
#include "../utility.h"

namespace PixelMaestro {
	RandomAnimation::RandomAnimation(Section* section, bool reverse, Orientations orientation) : ColorAnimation(section, reverse, orientation) { }

	void RandomAnimation::update() {
		for (unsigned int pixel = 0; pixel < section_->get_num_pixels(); pixel++) {
			section_->set_one(pixel, &colors_[Utility::rand() % num_colors_]);
		}
	}
}
