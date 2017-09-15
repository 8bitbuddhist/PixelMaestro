#include "../utility.h"
#include "sparkleanimation.h"

namespace PixelMaestro {
	SparkleAnimation::SparkleAnimation(Colors::RGB* colors, unsigned char num_colors, unsigned char threshold) : Animation(colors, num_colors) {
		this->threshold_ = threshold;
	}

	/**
	 * Sets the chances of a Pixel turning on.
	 * @param threshold Chance that an individual Pixel will turn on (0 - 255).
	 */
	void SparkleAnimation::set_threshold(unsigned char threshold) {
		this->threshold_ = threshold;
	}

	void SparkleAnimation::update(Section* section) {
		if (orientation_ == VERTICAL) {
			for (unsigned short x = 0; x < section->get_dimensions()->x; x++) {
				for (unsigned short y = 0; y < section->get_dimensions()->y; y++) {
					if ((Utility::rand(255)) <= threshold_) {
						section->set_one(y, x, get_color_at_index(x));
					}
					else {
						section->set_one(y, x, &Colors::BLACK);
					}
				}
			}
		}
		else {	// Horizontal
			for (unsigned short y = 0; y < section->get_dimensions()->y; y++) {
				for (unsigned short x = 0; x < section->get_dimensions()->x; x++) {
					if ((Utility::rand(255)) <= threshold_) {
						section->set_one(x, y, get_color_at_index(x));
					}
					else {
						section->set_one(x, y, &Colors::BLACK);
					}
				}
			}
		}
	}
}

