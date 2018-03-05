#include <math.h>
#include "radialanimation.h"

namespace PixelMaestro {
	RadialAnimation::RadialAnimation(Section* section) : MappedAnimation(section) {
		type_ = AnimationType::Radial;
	}

	/**
	 * Returns the resolution of each radial.
	 * @return Radial resolution.
	 */
	uint8_t RadialAnimation::get_resolution() const {
		return resolution_;
	}

	void RadialAnimation::map() {
		Point center = get_center();
		if (orientation_ == Orientation::Vertical) {
			// For each Pixel, calculate the slope from the center.
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					if (x == center.x || y == center.y) {
						map_[y][x] = 0;
					}
					else {
						map_[y][x] = ((y - center.y) / (float)(x - center.x)) * resolution_;
					}
				}
			}
		}
		else {	// Horizontal
			// For each Pixel, calculate its distance from the center of the grid, then use the distance to choose the index of the correct color.
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				uint16_t y_squared_ = pow(y - center.y, 2);
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					map_[y][x] = sqrt(pow(x - center.x, 2) + y_squared_);
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
	}

	void RadialAnimation::update() {
		// Override MappedAnimation::update() so we can call map() on section resize.
		if (dimensions_ != *section_->get_dimensions()) {
			rebuild_map();
			map();
			dimensions_	= *section_->get_dimensions();
		}

		// Remap if the orientation changes.
		if (orientation_ != last_orientation_) {
			map();
			last_orientation_ = orientation_;
		}

		for (uint8_t x = 0; x < dimensions_.x; x++) {
			for (uint8_t y = 0; y < dimensions_.y; y++) {
				section_->set_one(x, y, palette_->get_color_at_index(map_[y][x] + cycle_index_));
			}
		}

		update_cycle(0, palette_->get_size());
	}

	RadialAnimation::~RadialAnimation() {}
}
