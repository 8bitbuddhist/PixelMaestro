/*
	Pixel.cpp - Library for controlling a single RGB.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
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
		step_.r = 0;
		step_.g = 0;
		step_.b = 0;
		step_.count = 0;
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
		step_.r = (next_color.r - current_color_.r) / (float)step_count;
		step_.g = (next_color.g - current_color_.g) / (float)step_count;
		step_.b = (next_color.b - current_color_.b) / (float)step_count;
		step_.count = step_count;
	}

	/**
		Main update routine.
		Checks for and applies color changes.
	*/
	Colors::RGB Pixel::update() {
		if (step_.count > 0) {
			current_color_.r += step_.r;
			current_color_.g += step_.g;
			current_color_.b += step_.b;

			step_.count--;
		}

		return current_color_;
	}
}
