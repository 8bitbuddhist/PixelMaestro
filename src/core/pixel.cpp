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
		Sets the LED's target color.

		@param color Target color.
		@param fade Whether to fade to the next color.
		@param cycle_interval The amount of time to go from the current color to next_color.
		@param refresh_rate The refresh rate of the section. Used to calculate color events (if fading).
	*/
	void Pixel::set_next_color(Colors::RGB next_color, bool fade, uint16_t cycle_interval, uint16_t refresh_rate) {
		// Only trigger an update if the colors don't match.
		if (next_color != current_color_) {
			/*
				Calculate the number of steps between the current color and the next color.
				Use the refresh rate to determine the number of steps to take during the event.
				If not fading, just jump one single step.
			*/
			float diff;
			if (fade) {
				diff = cycle_interval / (float)refresh_rate;
			}
			else {
				diff = 1;
			}

			step_[0] = (next_color.r - current_color_.r) / diff;
			step_[1] = (next_color.g - current_color_.g) / diff;
			step_[2] = (next_color.b - current_color_.b) / diff;
			step_count_ = diff;
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
