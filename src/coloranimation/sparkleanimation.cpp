#include "../utility.h"
#include "sparkleanimation.h"

namespace PixelMaestro {
	SparkleAnimation::SparkleAnimation(Section* section, bool reverse, Orientations orientation, unsigned char threshold) : ColorAnimation(section, reverse, orientation) {
		this->threshold_ = threshold;
	}

	void SparkleAnimation::update() {
		for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
			for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
				if ((Utility::rand() % 100) > threshold_) {
					section_->set_one(row, column, &colors_[get_color_index(column)]);
				}
				else {
					section_->set_one(row, column, &Colors::BLACK);
				}
			}
		}
	}
}

