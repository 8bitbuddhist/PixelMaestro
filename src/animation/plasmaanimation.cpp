#include <math.h>
#include "plasmaanimation.h"

namespace PixelMaestro {
	PlasmaAnimation::PlasmaAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Plasma;
		map();
	}

	/**
	 * Returns the plasma resolution.
	 * @return Plasma resolution.
	 */
	float PlasmaAnimation::get_resolution() const {
		return resolution_;
	}

	/**
	 * Returns the plasma size.
	 * @return Plasma size.
	 */
	float PlasmaAnimation::get_size() const {
		return size_;
	}

	/**
	 * Updates the plasma map.
	 * This occurs whenever we change the grid size, plasma size, or plasma resolution.
	 */
	void PlasmaAnimation::map() {
		for (uint16_t y = 0; y < dimensions_.y; y++) {
			for (uint16_t x = 0; x < dimensions_.x; x++) {
				set_map_color_index(x, y, ((resolution_ + (resolution_ * sin(x / size_))) + (resolution_ + (resolution_ * sin(y / size_)))) / 2);
			}
		}
	}

	/**
	 * Sets the resolution (sharpness) of each plasma.
	 * @param resolution Plasma resolution.
	 */
	void PlasmaAnimation::set_resolution(float resolution) {
		this->resolution_ = resolution;
		map();
	}

	/**
	 * Sets the size of each plasma.
	 * @param size Plasma size.
	 */
	void PlasmaAnimation::set_size(float size) {
		this->size_ = size;
		map();
	}

	void PlasmaAnimation::update() {
		update_cycle(0, palette_->get_num_colors());
	}
}
