/*
	Pixel.cpp - Library for controlling a single RGB.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

#include "../utility.h"
#include "colors.h"
#include "pixel.h"

namespace PixelMaestro {
	/**
		Returns the current color.

		@return The current color.
	*/
	Colors::RGB* Pixel::get_color() {
		return &current_color_;
	}

	/**
		Sets the Pixel's target color.

		@param next_color Target color.
		@param step_count The number of steps to the target color.
	*/
	void Pixel::set_next_color(Colors::RGB next_color, uint8_t step_count) {
		// Only trigger an update if the colors don't match.
		if (next_color != current_color_) {
			step_[0] = (next_color.r - current_color_.r) / (float)step_count;
			step_[1] = (next_color.g - current_color_.g) / (float)step_count;
			step_[2] = (next_color.b - current_color_.b) / (float)step_count;
			step_count_ = step_count;
		}
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
	}
}
