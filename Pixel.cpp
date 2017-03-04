/**
	Pixel.cpp - Library for controlling a single RGB pixel
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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
		@param interval Time between color changes.
	*/
	void Pixel::setNextColor(Colors::RGB *nextColor, bool fade, unsigned char interval) {
		// Only trigger an update if the colors don't match.
		if (nextColor != next_color_) {
			previous_color_ = next_color_;
			next_color_ = nextColor;

			/* If fading, calculate the steps between the current color and the next color.
			This ensures all transitions take the same amount of time.
			*/
			if (fade) {
				step_size_[0] = abs(next_color_->r - previous_color_->r) / interval;
				step_size_[1] = abs(next_color_->g - previous_color_->g) / interval;
				step_size_[2] = abs(next_color_->b - previous_color_->b) / interval;

				step_count_ = interval;
			}
			else {
				step_count_ = 0;
			}
		}
	}

	/**
		Main update routine.
	*/
	void Pixel::update() {
		// If we're fading, we need to increment (or decrement) by step_size_.
		if (step_count_ > 0) {

			// Red
			if (next_color_->r > current_color_.r) {
				current_color_.r += step_size_[0];
			}
			else if (next_color_->r < current_color_.r) {
				current_color_.r -= step_size_[0];
			}

			// Green
			if (next_color_->g > current_color_.g) {
				current_color_.g += step_size_[1];
			}
			else if (next_color_->g < current_color_.g) {
				current_color_.g -= step_size_[1];
			}

			// Blue
			if (next_color_->b > current_color_.b) {
				current_color_.b += step_size_[2];
			}
			else if (next_color_->b < current_color_.b) {
				current_color_.b -= step_size_[2];
			}

			step_count_ --;
		}
		else {
			current_color_ = *next_color_;
		}
	}
}
