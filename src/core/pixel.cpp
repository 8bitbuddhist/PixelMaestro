/*
	Pixel.cpp - Library for controlling a single RGB.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

#include "../utility.h"
#include "colors.h"
#include "pixel.h"

namespace PixelMaestro {

	uint8_t Pixel::step_count_ = 0;

	/**
	 * Clears the Pixel's color values.
	 */
	void Pixel::clear() {
		current_color_ = {0, 0, 0};

		#ifndef DISABLE_COLOR_BUFFER
			step_ = {0, 0, 0};
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
	void Pixel::set_next_color(const Colors::RGB& next_color) {
	#ifndef DISABLE_COLOR_BUFFER
		if (Pixel::step_count_ > 0) {
			step_.r = (next_color.r - current_color_.r) / (float)Pixel::step_count_;
			step_.g = (next_color.g - current_color_.g) / (float)Pixel::step_count_;
			step_.b = (next_color.b - current_color_.b) / (float)Pixel::step_count_;
		}
		else {
			current_color_ = next_color;
		}
	#else
			current_color_ = next_color;
	#endif
	}

	/**
	 * Sets the number of steps between color changes. Only applies if fading is enabled.
	 * @param step_count Number of steps to fade colors during transitions.
	 */
	void Pixel::set_step_count(uint8_t step_count) {
		#ifndef DISABLE_COLOR_BUFFER
			Pixel::step_count_ = step_count;
		#endif
	}

	/**
		Main update routine.
		Checks for and applies color changes.
	*/
	void Pixel::update() {
		#ifndef DISABLE_COLOR_BUFFER
		// WARNING: This can be imprecise, especially with small or gradual color changes.
		if (Pixel::step_count_ > 0) {
			current_color_.r += step_.r;
			current_color_.g += step_.g;
			current_color_.b += step_.b;
		}
		#endif
	}
}
