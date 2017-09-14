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

		@param color New color to store.
		@param fade Whether to fade to the next color.
		@param cycle_interval The amount of time to go from the current color to next_color.
		@param refresh_rate The refresh rate of the section. Used to calculate color events (if fading).
	*/
	void Pixel::set_next_color(Colors::RGB* next_color, bool fade, unsigned short cycle_interval, unsigned short refresh_rate) {
		// Only trigger an update if the colors don't match.
		if (next_color != nullptr && next_color != next_color_) {
			next_color_ = next_color;

			/*
				If fading, calculate the steps between the current color and the next color.
				Use the refresh rate to determine the number of steps to take during the event.
			*/
			if (fade) {
				float diff = cycle_interval / (float)refresh_rate;
				step_ = {
					(unsigned char)(Utility::abs_int(next_color_->r - current_color_.r) / diff),
					(unsigned char)(Utility::abs_int(next_color_->g - current_color_.g) / diff),
					(unsigned char)(Utility::abs_int(next_color_->b - current_color_.b) / diff)
				};
				step_count_ = diff;
			}
		}
	}

	/**
		Main update routine.
	*/
	void Pixel::update() {
		/*
		 * If fading, run through each step and add (or subtract) the step amount.
		 * At the end of the run (or if we're not fading), set current_color_ = next_color_.
		 */
		if (step_count_ > 0) {
			// Red
			if (next_color_->r > current_color_.r) {
				current_color_.r += step_.r;
			}
			else if (next_color_->r < current_color_.r) {
				current_color_.r -= step_.r;
			}

			// Green
			if (next_color_->g > current_color_.g) {
				current_color_.g += step_.g;
			}
			else if (next_color_->g < current_color_.g) {
				current_color_.g -= step_.g;
			}

			// Blue
			if (next_color_->b > current_color_.b) {
				current_color_.b += step_.b;
			}
			else if (next_color_->b < current_color_.b) {
				current_color_.b -= step_.b;
			}

			step_count_--;
		}
		else {
			current_color_ = *next_color_;
		}
	}
}
