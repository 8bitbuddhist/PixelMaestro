#include "../utility.h"
#include "sparkleanimation.h"

namespace PixelMaestro {
	SparkleAnimation::SparkleAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Sparkle;
		map();
	}

	/**
	 * Returns the threshold for activating a Pixel.
	 * @return Activation threshold.
	 */
	uint8_t SparkleAnimation::get_threshold() const {
		return threshold_;
	}

	/**
	 * Sets the chances of a Pixel turning on.
	 * @param threshold Chance that an individual Pixel will turn on (0 - 255).
	 */
	void SparkleAnimation::set_threshold(uint8_t threshold) {
		this->threshold_ = threshold;
	}

	void SparkleAnimation::map() {
		if (orientation_ == Orientation::Vertical) {
			for (uint16_t x = 0; x < section_.get_dimensions().x; x++) {
				for (uint16_t y = 0; y < section_.get_dimensions().y; y++) {
					if (Utility::rand(255) <= threshold_) {
						set_map_color_index(x, y, y);
					}
					else {
						set_map_color_index(x, y, 255);
					}
				}
			}
		}
		else {	// Horizontal
			for (uint16_t y = 0; y < section_.get_dimensions().y; y++) {
				for (uint16_t x = 0; x < section_.get_dimensions().x; x++) {
					if (Utility::rand(255) <= threshold_) {
						set_map_color_index(x, y, x);
					}
					else {
						set_map_color_index(x, y, 255);
					}
				}
			}
		}
	}

	void SparkleAnimation::update() {
		map();
	}
}

