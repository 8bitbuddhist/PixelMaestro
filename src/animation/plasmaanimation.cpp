#include <math.h>
#include "plasmaanimation.h"

namespace PixelMaestro {
	PlasmaAnimation::PlasmaAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Plasma;
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
	 * Sets the resolution (sharpness) of each plasma.
	 * @param resolution Plasma resolution.
	 */
	void PlasmaAnimation::set_resolution(float resolution) {
		this->resolution_ = resolution;
	}

	/**
	 * Sets the size of each plasma.
	 * @param size Plasma size.
	 */
	void PlasmaAnimation::set_size(float size) {
		this->size_ = size;
	}

	void PlasmaAnimation::update() {
		int color_index;

		for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				color_index = ((resolution_ + (resolution_ * sin(x / size_))) + (resolution_ + (resolution_ * sin(y / size_)))) / 2;
				section_->set_one(x, y, palette_->get_color_at_index(color_index + cycle_index_));
			}
		}

		update_cycle(0, palette_->get_size());
	}

	PlasmaAnimation::~PlasmaAnimation() {}
}
