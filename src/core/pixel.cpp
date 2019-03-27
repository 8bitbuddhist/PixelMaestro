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
		next_color_ = {0, 0, 0};
		step_count_ = 0;
	}

	/**
		Returns the current color.

		@return The current color.
	*/
	const Colors::RGB& Pixel::get_color() {
		return current_color_;
	}

	/**
		Sets the Pixel's target color.

		@param next_color Target color.
		@param step_count The number of steps to the target color.
	*/
	void Pixel::set_next_color(const Colors::RGB& next_color, uint8_t step_count) {
		this->next_color_ = next_color;
		step_[0] = (next_color.r - current_color_.r) / (float)step_count;
		step_[1] = (next_color.g - current_color_.g) / (float)step_count;
		step_[2] = (next_color.b - current_color_.b) / (float)step_count;
		step_count_ = step_count;
	}

	/**
		Main update routine.
		Checks for and applies color changes.
	*/
	void Pixel::update() {
		if (step_count_ > 0) {
			current_color_.r += step_[0];
			current_color_.g += step_[1];
			current_color_.b += step_[2];

			step_count_--;
		}
		else {
			current_color_ = next_color_;
		}
	}
}
