/*
 * MappedAnimation - Abstract Animation class that maps palette colors to pixels.
 * Used for Animations that need to either perform expensive per-pixel calculations, or store temporary grid data to a buffer.
 * Derived classes implement map() and override update().
 * See FireAnimation and MandelbrotAnimation for examples.
 */

#include "mappedanimation.h"

namespace PixelMaestro {
	MappedAnimation::MappedAnimation(Section& section) : Animation(section) {
		// Initial map build
		rebuild_map();
	}

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

		dimensions_ = *section_.get_dimensions();

		map_ = new uint8_t*[dimensions_.y];
		for (uint8_t y = 0; y < dimensions_.y; y++) {
			map_[y]	= new uint8_t[dimensions_.x] {0};
		}
	}

	void MappedAnimation::set_pixel_map(uint8_t x, uint8_t y, uint8_t color_index) {
		map_[y][x] = color_index;
	}

	/**
	 * Updates the Animation.
	 * On each update, check to see if the grid size has changed. If so, rebuild the map.
	 */
	void MappedAnimation::update() {
		// Add orientation check
		if (dimensions_ != *section_.get_dimensions()) {
			rebuild_map();
			map();
		}

		/* TODO: Account for fading.
		 *	Note that MappedAnimation::update() triggers per timer refresh, not per Maestro refresh.
		 *	So we would need to merge with Animation::update() before handling fade logic.
		 */
		for (uint16_t x = 0; x < section_.get_dimensions()->x; x++) {
			for (uint16_t y = 0; y < section_.get_dimensions()->y; y++) {
				// Color index 255 reserved for black
				if (map_[y][x] == 255) {
					section_.set_one(x, y, Colors::RGB(0, 0, 0), timer_->get_step_count());
				}
				else {
					section_.set_one(x,
						y,
						palette_->get_color_at_index(map_[y][x] + cycle_index_),
						timer_->get_step_count()
					);
				}
			}
		}
	}

	MappedAnimation::~MappedAnimation() {
		for (uint8_t y = 0; y < dimensions_.y; y++) {
			delete [] map_[y];
		}
		delete [] map_;
	}
}
