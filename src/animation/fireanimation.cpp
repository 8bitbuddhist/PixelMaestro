#include "../utility.h"
#include "fireanimation.h"

namespace PixelMaestro {
	FireAnimation::FireAnimation(Section* section) : MappedAnimation(section)	{
		type_ = AnimationType::Fire;
	}

	/**
	 * Returns the multiplier, which changes the height of the flames.
	 * @return Flame multiplier.
	 */
	uint8_t FireAnimation::get_multiplier() const {
		return this->multiplier_;
	}

	/**
	 * Update the map.
	 * This occurs on each frame.
	 */
	void FireAnimation::map() {
		// Randomize the bottom row
		for (uint16_t x = 0; x < dimensions_.x; x++) {
			// If a Palette has not been set, use a default value
			if (palette_ != nullptr) {
				map_[dimensions_.y - 1][x] = Utility::abs_int(32768 + Utility::rand()) % palette_->get_num_colors();
			}
			else {
				map_[dimensions_.y - 1][x] = Utility::abs_int(32768 + Utility::rand()) % 10;
			}
		}

		// Calculate the remaining Pixels based on the bottom row
		for (uint16_t y = 0; y < dimensions_.y - 1; y++) {
			for (uint16_t x = 0; x < dimensions_.x; x++) {
				// http://lodev.org/cgtutor/fire.html
				map_[y][x] =
					(map_[(y + 1) % dimensions_.y][(x - 1 + dimensions_.x) % dimensions_.x] +
					map_[(y + 1) % dimensions_.y][x % dimensions_.x] +
					map_[(y + 1) % dimensions_.y][(x + 1) % dimensions_.x] +
					map_[(y + 2) % dimensions_.y][x % dimensions_.x]) *
					(float)((this->multiplier_ + 200) / (float)1000);	// 200 is a magic number added to the multiplier to get a decently sized flame effect without hitting the limits of uint8_t.
			}
		}
	}

	/**
	 * Sets the multiplier, which determines the height of the flames.
	 * @param multiplier Flame height.
	 */
	void FireAnimation::set_multiplier(uint8_t multiplier) {
		this->multiplier_ = multiplier;
	}

	void FireAnimation::update() {
		MappedAnimation::update();
		// Rebuild the map on each frame
		map();

		// Apply the buffer to the Pixel grid
		for (uint16_t y = 0; y < dimensions_.y; y++) {
			for (uint16_t x = 0; x < dimensions_.x; x++) {
				section_->set_one(x, y, &palette_->get_colors()[map_[y][x] % palette_->get_num_colors()]);
			}
		}
	}

	FireAnimation::~FireAnimation() {}
}
