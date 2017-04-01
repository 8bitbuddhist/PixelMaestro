/**
	Pixel.cpp - Library for controlling a single RGB pixel.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

#include <stdlib.h>
#include "Colors.h"
#include "Pixel.h"

namespace PixelMaestro {
	/**
		Returns the current color.

		@return The current color.
	*/
	Colors::RGB *Pixel::getColor() {
		return &current_color_;
	}

	/**
		Returns the next color.

		@return The target color.
	*/
	Colors::RGB *Pixel::getNextColor() {
		return next_color_;
	}

	/**
		Returns the current step count.
		Used by RGBArray to determine when the LED has finished its cycle.

		@return The current step count.
	*/
	unsigned char Pixel::getStepCount() {
		return step_count_;
	}

	/**
		Sets the LED's target color.

		@param color New color to store.
		@param fade Whether to fade to the next color.
		@param speed Time until next color applies.
	*/
	void Pixel::setNextColor(Colors::RGB *nextColor, bool fade, unsigned char speed) {
		// Only trigger an update if the colors don't match.
		if (nextColor != next_color_) {
			previous_color_ = next_color_;
			next_color_ = nextColor;

			/*
				If fading, calculate the steps between the current color and the next color.
				This ensures all transitions take the same amount of time.
			*/
			if (fade && speed > 0) {
				step_ = {
					(unsigned char)(abs(next_color_->r - current_color_.r) / speed),
					(unsigned char)(abs(next_color_->g - current_color_.g) / speed),
					(unsigned char)(abs(next_color_->b - current_color_.b) / speed)
				};
			}

			step_count_ = speed;
		}
	}

	/**
		Main update routine.
	*/
	void Pixel::update(bool fade) {
		/*
			We measure the time between transitions using step_size_.
			This ensures a consistent wait time regardless of whether we're fading.
		*/
		if (step_count_ > 0) {

			if (fade) {
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
			}

			step_count_--;
		}
		else {
			current_color_ = *next_color_;
		}
	}
}
