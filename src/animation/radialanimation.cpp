#include <math.h>
#include "radialanimation.h"

namespace PixelMaestro {
	RadialAnimation::RadialAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Radial;
		map();
	}

	/**
	 * Returns the resolution of each radial.
	 * @return Radial resolution.
	 */
	uint8_t RadialAnimation::get_resolution() const {
		return resolution_;
	}

	/**
	 * Updates the map.
	 * This only occurs when the grid size or orientation changes.
	 */
	void RadialAnimation::map() {
		if (orientation_ == Orientation::Vertical || orientation_ == Orientation::VerticalFlipped) {
			// For each Pixel, calculate the slope from the center.
			for (uint16_t y = 0; y < dimensions_.y; y++) {
				int16_t y_distance = y - center_.y;
				for (uint16_t x = 0; x < dimensions_.x; x++) {
					if (x == center_.x || y == center_.y) {
						set_map_color_index(x, y, 0);
					}
					else {
						int16_t x_distance	= x - center_.x;
						double slope = (y_distance / (float)x_distance);
						set_map_color_index(x, y, static_cast<uint16_t>(slope * resolution_) % 255);
						// set_map_color_index(x, y, static_cast<uint16_t>(((y - center.y) / (float)(x - center.x)) * resolution_) % 255);


					}
				}
			}
		}
		else {	// Horizontal
			// For each Pixel, calculate its distance from the center of the grid, then use the distance to choose the index of the correct color.
			for (uint16_t y = 0; y < dimensions_.y; y++) {
				double y_squared_ = pow(y - (float)center_.y, 2);
				for (uint16_t x = 0; x < dimensions_.x; x++) {
					double x_squared = pow(x - (float)center_.x, 2);
					double distance = sqrt(x_squared + y_squared_);
					set_map_color_index(x, y, static_cast<uint8_t>(distance) % 255);
				}
			}
		}
	}

	/**
	 * Changes the size of each spoke (vertical mode only).
	 * @param resolution New resolution.
	 */
	void RadialAnimation::set_resolution(uint8_t resolution) {
		this->resolution_ = resolution;
		map();
	}

	void RadialAnimation::update() {
		update_frame(0, palette_->get_num_colors());
	}
}
