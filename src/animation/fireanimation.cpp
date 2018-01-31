#include "fireanimation.h"

namespace PixelMaestro {
	FireAnimation::FireAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors)	{
		type_ = AnimationType::Fire;

		// Initialize color index array
		color_indices_ = new uint8_t*[section_->get_dimensions()->y];
		for (uint8_t y = 0; y < section_->get_dimensions()->y; y++) {
			color_indices_[y] = new uint8_t[section_->get_dimensions()->x] {0};
		}
	}

	uint8_t FireAnimation::get_divisor() {
		return this->divisor_;
	}

	uint8_t FireAnimation::get_multiplier() {
		return this->multiplier_;
	}

	void FireAnimation::set_divisor(uint8_t divisor) {
		this->divisor_ = divisor;
	}

	void FireAnimation::set_multiplier(uint8_t multiplier) {
		this->multiplier_ = multiplier;
	}

	void FireAnimation::update() {
		// Initialize the bottom row
		for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
			//color_indices_[section_->get_dimensions()->y - 1][x] = Utility::rand(32768) % num_colors_;
			color_indices_[section_->get_dimensions()->y - 1][x] = Utility::abs_int(32768 + Utility::rand()) % num_colors_;
		}

		// Update the remaining pixels
		for (uint16_t y = 0; y < section_->get_dimensions()->y - 1; y++) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				// http://lodev.org/cgtutor/fire.html
				color_indices_[y][x] =
					((color_indices_[(y + 1) % section_->get_dimensions()->y][(x - 1 + section_->get_dimensions()->x) % section_->get_dimensions()->x] +
					color_indices_[(y + 1) % section_->get_dimensions()->y][x % section_->get_dimensions()->x] +
					color_indices_[(y + 1) % section_->get_dimensions()->y][(x + 1) % section_->get_dimensions()->x] +
					color_indices_[(y + 2) % section_->get_dimensions()->y][x % section_->get_dimensions()->x]) *
					this->multiplier_) / this->divisor_;

				/*
				 * fire[y][x] =
				((fire[(y + 1) % h][(x - 1 + w) % w]
				+ fire[(y + 1) % h][(x) % w]
				+ fire[(y + 1) % h][(x + 1) % w]
				+ fire[(y + 2) % h][(x) % w])
				* 32) / 129;
				*/
			}
		}

		for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				section_->set_one(x, y, &colors_[color_indices_[y][x] % num_colors_]);
			}
		}
	}

	FireAnimation::~FireAnimation() {
		for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
			delete [] color_indices_[y];
		}

		delete [] color_indices_;
	}
}
