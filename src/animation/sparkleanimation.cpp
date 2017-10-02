#include "../utility.h"
#include "sparkleanimation.h"

namespace PixelMaestro {
	SparkleAnimation::SparkleAnimation(Colors::RGB* colors, uint8_t num_colors, uint16_t speed, uint16_t pause, uint8_t threshold) : Animation(colors, num_colors, speed, pause) {
		type_ = Animation::Type::Sparkle;
		threshold_ = threshold;
	}

	/**
	 * Returns the threshold for activating a Pixel.
	 * @return Activation threshold.
	 */
	uint8_t SparkleAnimation::get_threshold() {
		return threshold_;
	}

	/**
	 * Sets the chances of a Pixel turning on.
	 * @param threshold Chance that an individual Pixel will turn on (0 - 255).
	 */
	void SparkleAnimation::set_threshold(uint8_t threshold) {
		this->threshold_ = threshold;
	}

	void SparkleAnimation::update(Section* section) {
		if (orientation_ == Orientation::Vertical) {
			for (uint16_t x = 0; x < section->get_dimensions()->x; x++) {
				for (uint16_t y = 0; y < section->get_dimensions()->y; y++) {
					if (Utility::rand(255) <= threshold_) {
						section->set_one(x, y, get_color_at_index(y));
					}
					else {
						section->set_one(x, y, &Colors::BLACK);
					}
				}
			}
		}
		else {	// Horizontal
			for (uint16_t y = 0; y < section->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < section->get_dimensions()->x; x++) {
					if (Utility::rand(255) <= threshold_) {
						section->set_one(x, y, get_color_at_index(x));
					}
					else {
						section->set_one(x, y, &Colors::BLACK);
					}
				}
			}
		}
	}

	SparkleAnimation::~SparkleAnimation() {}
}

