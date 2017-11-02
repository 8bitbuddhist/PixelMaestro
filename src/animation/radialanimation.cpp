#include <math.h>
#include "radialanimation.h"

namespace PixelMaestro {
	RadialAnimation::RadialAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Radial;
	}

	/**
	 * Returns the resolution of each radial.
	 * @return Radial resolution.
	 */
	uint8_t RadialAnimation::get_resolution() {
		return resolution_;
	}

	/**
	 * Changes the size of each spoke (vertical mode only).
	 * @param resolution New resolution.
	 */
	void RadialAnimation::set_resolution(uint8_t resolution) {
		this->resolution_ = resolution;
	}

	void RadialAnimation::update() {
		// Check if the size of the grid has changed.
		if (size_ != *section_->get_dimensions()) {
			size_ = *section_->get_dimensions();
			center_ = {
				(uint16_t)(size_.x / 2),
				(uint16_t)(size_.y / 2)
			};
		}

		if (orientation_ == Orientation::Vertical) {
			// For each Pixel, calculate the slope from the center.
			for (uint16_t y = 0; y < size_.y; y++) {
				for (uint16_t x = 0; x < size_.x; x++) {
					if (x == center_.x || y == center_.y) {
						slope_ = 0;
					}
					else {
						slope_ = ((y - center_.y) / (float)(x - center_.x)) * resolution_;
					}

					section_->set_one(x, y, get_color_at_index(slope_ + cycle_index_));
				}
			}
		}
		else {	// Horizontal
			// For each Pixel, calculate its distance from the center of the grid, then use the distance to choose the index of the correct color.
			for (uint16_t y = 0; y < size_.y; y++) {
				y_squared_ = pow(y - center_.y, 2);
				for (uint16_t x = 0; x < size_.x; x++) {
					distance_ = sqrt(pow(x - center_.x, 2) + y_squared_);
					section_->set_one(x, y, get_color_at_index(distance_ + cycle_index_));
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	RadialAnimation::~RadialAnimation() {}
}
