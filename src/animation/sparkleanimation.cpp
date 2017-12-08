#include "../colorpresets.h"
#include "../utility.h"
#include "sparkleanimation.h"

namespace PixelMaestro {
	SparkleAnimation::SparkleAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors, uint8_t threshold) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Sparkle;
		threshold_ = threshold;
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

	void SparkleAnimation::update() {
		if (orientation_ == Orientation::Vertical) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					if (Utility::rand(255) <= threshold_) {
						section_->set_one(x, y, get_color_at_index(y));
					}
					else {
						section_->set_one(x, y, &ColorPresets::BLACK);
					}
				}
			}
		}
		else {	// Horizontal
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					if (Utility::rand(255) <= threshold_) {
						section_->set_one(x, y, get_color_at_index(x));
					}
					else {
						section_->set_one(x, y, &ColorPresets::BLACK);
					}
				}
			}
		}
	}

	SparkleAnimation::~SparkleAnimation() {}
}

