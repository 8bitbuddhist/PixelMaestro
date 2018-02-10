#include "../utility.h"
#include "fireanimation.h"

namespace PixelMaestro {
	FireAnimation::FireAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : MappedAnimation(section, colors, num_colors)	{
		type_ = AnimationType::Fire;
	}

	uint8_t FireAnimation::get_multiplier() {
		return this->multiplier_;
	}

	void FireAnimation::map() {
		// Initialize the bottom row buffer
		for (uint16_t x = 0; x < dimensions_.x; x++) {
			map_[dimensions_.y - 1][x] = Utility::abs_int(32768 + Utility::rand()) % num_colors_;
		}

		// Set the buffer for the remaining pixels
		for (uint16_t y = 0; y < dimensions_.y - 1; y++) {
			for (uint16_t x = 0; x < dimensions_.x; x++) {
				// http://lodev.org/cgtutor/fire.html
				map_[y][x] =
					(map_[(y + 1) % dimensions_.y][(x - 1 + dimensions_.x) % dimensions_.x] +
					map_[(y + 1) % dimensions_.y][x % dimensions_.x] +
					map_[(y + 1) % dimensions_.y][(x + 1) % dimensions_.x] +
					map_[(y + 2) % dimensions_.y][x % dimensions_.x]) *
					(float)((this->multiplier_ + 200) / (float)1000);	// 200 is just a magic number added to the multiplier to get a decently sized flame effect without hitting the limits of uint8_t.
			}
		}
	}

	void FireAnimation::set_multiplier(uint8_t multiplier) {
		this->multiplier_ = multiplier;
	}

	void FireAnimation::update() {
		MappedAnimation::update();
		map();

		// Apply the buffer to the Pixel grid
		for (uint16_t y = 0; y < dimensions_.y; y++) {
			for (uint16_t x = 0; x < dimensions_.x; x++) {
				section_->set_one(x, y, &colors_[map_[y][x] % num_colors_]);
			}
		}
	}

	FireAnimation::~FireAnimation() {}
}
