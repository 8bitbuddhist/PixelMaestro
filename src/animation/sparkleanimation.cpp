#include "../utility.h"
#include "sparkleanimation.h"

namespace PixelMaestro {
	SparkleAnimation::SparkleAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors, unsigned char threshold) : Animation(section, colors, num_colors) {
		this->threshold_ = threshold;
	}

	void SparkleAnimation::update() {
		if (orientation_ == VERTICAL) {
			for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
				for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
					if ((Utility::rand() % 100) > threshold_) {
						section_->set_one(column, row, get_color_at_index(column));
					}
					else {
						section_->set_one(column, row, &Colors::BLACK);
					}
				}
			}
		}
		else {	// Horizontal
			for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
				for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
					if ((Utility::rand() % 100) > threshold_) {
						section_->set_one(row, column, get_color_at_index(column));
					}
					else {
						section_->set_one(row, column, &Colors::BLACK);
					}
				}
			}
		}
	}
}

