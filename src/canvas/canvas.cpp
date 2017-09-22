/*
 * Canvas - Displays the Section's underlying Animation.
 */

#include "canvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. This initializes the Pattern array.
	 * AnimationCanvases "paint" by showing the Section's underlying Animation.
	 * @param section The Canvas' parent Section.
	 */
	Canvas::Canvas(Section* section) : BaseCanvas(section) {
		initialize_pattern();
	}

	/**
	 * Enables the pixel at the specified index.
	 * @param pixel Pixel to activate.
	 */
	void Canvas::activate(unsigned int pixel) {
		pattern_[pixel] = 1;
	}

	/**
	 * Deactivates (turns off) the pixel at the specified index.
	 * @param pixel Pixel to deactivate.
	 */
	void Canvas::deactivate(unsigned int pixel) {
		pattern_[pixel] = 0;
	}

	/**
	 * Returns the color of the Pixel at the specified index.
	 * If the Pixel is activated, return the color of the underlying Animation.
	 * If the Pixel is deactivated, return black.
	 * @param pixel Index of the pixel to check.
	 * @return Pixel's color.
	 */
	Colors::RGB Canvas::get_pixel_color(unsigned int pixel) {
		if (pattern_[pixel] == 0) {
			return Colors::BLACK;
		}
		else {
			return *section_->get_pixel(pixel)->get_color();
		}
	}

	/**
	 * Reinitializes the pattern array.
	 */
	void Canvas::initialize_pattern() {
		if (pattern_ != nullptr) {
			delete[] pattern_;
		}
		pattern_ = new bool[section_->get_dimensions()->size()] {0};
	}

	Canvas::~Canvas() {
		delete[] pattern_;
	}
}
