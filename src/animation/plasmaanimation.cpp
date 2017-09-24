#include <math.h>
#include "plasmaanimation.h"

namespace PixelMaestro {
	PlasmaAnimation::PlasmaAnimation(Colors::RGB* colors, unsigned char num_colors, unsigned short speed, unsigned short pause, float size, float resolution) : Animation(colors, num_colors, speed, pause) {
		resolution_ = resolution;
		size_ = size;
	}

	/**
	 * Returns the plasma resolution.
	 * @return Plasma resolution.
	 */
	float PlasmaAnimation::get_resolution() {
		return resolution_;
	}

	/**
	 * Returns the plasma size.
	 * @return Plasma size.
	 */
	float PlasmaAnimation::get_size() {
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

	void PlasmaAnimation::update(Section* section) {
		int color_index;

		for (unsigned short y = 0; y < section->get_dimensions()->y; y++) {
			for (unsigned short x = 0; x < section->get_dimensions()->x; x++) {
				color_index = ((resolution_ + (resolution_ * sin(x / size_))) + (resolution_ + (resolution_ * sin(y / size_)))) / 2;
				section->set_one(x, y, get_color_at_index(color_index + cycle_index_));
			}
		}

		update_cycle(0, num_colors_);
	}

	PlasmaAnimation::~PlasmaAnimation() {}
}
