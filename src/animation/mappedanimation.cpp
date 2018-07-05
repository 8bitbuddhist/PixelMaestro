/*
 * MappedAnimation - Abstract Animation class that maps palette colors to pixels.
 * Used for Animations that need to either perform expensive per-pixel calculations, or store temporary grid data to a buffer.
 * Derived classes implement map() and override update().
 * See FireAnimation and MandelbrotAnimation for examples.
 */

#include "mappedanimation.h"

namespace PixelMaestro {
	MappedAnimation::MappedAnimation(Section* section) : Animation(section) { }

	/**
	 * Regenerates the color-to-pixel map.
	 * Only runs when the grid changes dimensions.
	 */
	void MappedAnimation::rebuild_map() {
		// Regenerate the color-to-pixel mapping.
		for (uint8_t y = 0; y < dimensions_.y; y++) {
			delete [] map_[y];
		}
		delete [] map_;

		dimensions_ = *section_->get_dimensions();

		map_ = new uint8_t*[dimensions_.y];
		for (uint8_t y = 0; y < dimensions_.y; y++) {
			map_[y]	= new uint8_t[dimensions_.x] {0};
		}

		map();
	}

	/**
	 * Updates the Animation.
	 * On each update, check to see if the grid size has changed. If so, rebuild the color-to-pixel map.
	 */
	void MappedAnimation::update() {
		if (dimensions_ != *section_->get_dimensions()) {
			rebuild_map();
		}
	}

	MappedAnimation::~MappedAnimation() {
		for (uint8_t y = 0; y < dimensions_.y; y++) {
			delete [] map_[y];
		}
		delete [] map_;
	}
}
