#include "../utility.h"
#include "sparkleanimation.h"

namespace PixelMaestro {
	SparkleAnimation::SparkleAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors, unsigned char threshold) : Animation(section, colors, num_colors) {
		this->threshold_ = threshold;
	}

	void SparkleAnimation::update() {
		if (orientation_ == VERTICAL) {
			for (unsigned short x = 0; x < section_->get_dimensions()->x; x++) {
				for (unsigned short y = 0; y < section_->get_dimensions()->y; y++) {
					if ((Utility::rand() % 100) > threshold_) {
						section_->set_one(y, x, get_color_at_index(x));
					}
					else {
						section_->set_one(y, x, &Colors::BLACK);
					}
				}
			}
		}
		else {	// Horizontal
			for (unsigned short y = 0; y < section_->get_dimensions()->y; y++) {
				for (unsigned short x = 0; x < section_->get_dimensions()->x; x++) {
					if ((Utility::rand() % 100) > threshold_) {
						section_->set_one(x, y, get_color_at_index(x));
					}
					else {
						section_->set_one(x, y, &Colors::BLACK);
					}
				}
			}
		}
	}
}

