/*
	Pixel.cpp - Class for controlling a single RGB LED.
*/

#include "../utility.h"
#include "colors.h"
#include "pixel.h"

namespace PixelMaestro {

	/**
	 * Sets the Pixel's current color to its next color.
	 * Only applies when PIXEL_ENABLE_ACCURATE_FADING is enabled.
	 */
	void Pixel::apply_next_color() {
		#ifdef PIXEL_ENABLE_ACCURATE_FADING
			current_color_ = next_color_;
		#endif
	}

	/**
	 * Clears the Pixel's color values.
	 */
	void Pixel::clear() {
		current_color_ = {0, 0, 0};

		#ifdef PIXEL_ENABLE_FADING
			step_ = {0, 0, 0};

			#ifdef PIXEL_ENABLE_ACCURATE_FADING
				next_color_ = {0, 0, 0};
			#endif
		#endif
	}

	/**
		Returns the current color.

		@return The current color.
	*/
	Colors::RGB& Pixel::get_color() {
		return this->current_color_;
	}

	/**
		Sets the Pixel's target color.

		@param next_color Target color.
		@param step_count The number of steps to the target color.
	*/
	void Pixel::set_next_color(const Colors::RGB& next_color, uint8_t step_count) {
		#ifdef PIXEL_ENABLE_FADING
			step_.r = (next_color.r - current_color_.r) / (float)step_count;
			step_.g = (next_color.g - current_color_.g) / (float)step_count;
			step_.b = (next_color.b - current_color_.b) / (float)step_count;

			#ifdef PIXEL_ENABLE_ACCURATE_FADING
				next_color_ = next_color;
			#endif
		#else
			current_color_ = next_color;
		#endif
	}

	/**
		Main update routine.
		Checks for and applies color changes.
	*/
	void Pixel::update() {
		#ifdef PIXEL_ENABLE_FADING
			current_color_.r += step_.r;
			current_color_.g += step_.g;
			current_color_.b += step_.b;
		#endif
	}
}
