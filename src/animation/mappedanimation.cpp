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

		map_ = new uint8_t*[section_->get_dimensions()->y];
		for (uint8_t y = 0; y < section_->get_dimensions()->y; y++) {
			map_[y]	= new uint8_t[section_->get_dimensions()->x] {0};
		}
	}

	/**
	 * Updates the Animation.
	 * On each update, check to see if the grid size has changed. If so, remap the colors.
	 */
	void MappedAnimation::update() {
		// Rebuild if the grid size has changed.
		if (dimensions_ != *section_->get_dimensions()) {
			rebuild_map();
			dimensions_	= *section_->get_dimensions();
		}
	}

	MappedAnimation::~MappedAnimation() {
		for (uint8_t y = 0; y < dimensions_.y; y++) {
			delete [] map_[y];
		}
		delete [] map_;
	}
}