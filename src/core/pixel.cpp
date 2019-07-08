/*
	Pixel.cpp - Class for controlling a single RGB LED.
*/

#include "../utility.h"
#include "colors.h"
#include "pixel.h"

namespace PixelMaestro {

	/**
	 * Clears the Pixel's color values.
	 */
	void Pixel::clear() {
		current_color_ = {0, 0, 0};

#ifndef PIXEL_DISABLE_FADING
		step_ = {0, 0, 0};

#ifdef PIXEL_ENABLE_ACCURATE_FADING
		next_color_ = {0, 0, 0};
#endif // PIXEL_ENABLE_ACCURATE_FADING
#endif // PIXEL_DISABLE_FADING
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
#ifndef PIXEL_DISABLE_FADING
		step_.r = (next_color.r - current_color_.r) / (float)step_count;
		step_.g = (next_color.g - current_color_.g) / (float)step_count;
		step_.b = (next_color.b - current_color_.b) / (float)step_count;

#ifdef PIXEL_ENABLE_ACCURATE_FADING
			next_color_ = next_color;
#endif // PIXEL_ENABLE_ACCURATE_FADING
#else
		current_color_ = next_color;
#endif // PIXEL_DISABLE_FADING
	}

	/**
		Main update routine.
		Checks for and applies color changes.
	*/
	void Pixel::update(bool apply_next_color) {
#ifndef PIXEL_DISABLE_FADING
		current_color_.r += step_.r;
		current_color_.g += step_.g;
		current_color_.b += step_.b;

#ifdef PIXEL_ENABLE_ACCURATE_FADING
		if (apply_next_color) {
			current_color_ = next_color_;
		}
#endif // PIXEL_ENABLE_ACCURATE_FADING
#endif // PIXEL_DISABLE_FADING
	}
}
