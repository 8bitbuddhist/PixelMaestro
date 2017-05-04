/*
	Pixel.cpp - Library for controlling a single RGB.
	Inspired by RGBMood (http://forum.arduino.cc/index.php?topic=90160.0)
*/

#include <stdlib.h>
#include "../include/Colors.h"
#include "../include/Pixel.h"

namespace PixelMaestro {
	/**
		Returns the current color.

		@return The current color.
	*/
	Colors::RGB *Pixel::getColor() {
		return &current_color_;
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
		@param cycleInterval The amount of time to go from the current color to nextColor.
		@param refreshRate The refresh rate of the section. Used to calculate color transitions (if fading).
	*/
	void Pixel::setNextColor(Colors::RGB *nextColor, bool fade, unsigned short cycleInterval, unsigned short refreshRate) {
		// Only trigger an update if the colors don't match.
		if (nextColor != next_color_) {
			next_color_ = nextColor;

			/*
				If fading, calculate the steps between the current color and the next color.
				Use the refresh rate to determine the number of steps to take during the transition.
			*/
			if (fade) {
				float diff = cycleInterval / (float)refreshRate;
				step_ = {
					(unsigned char)(abs(next_color_->r - current_color_.r) / diff),
					(unsigned char)(abs(next_color_->g - current_color_.g) / diff),
					(unsigned char)(abs(next_color_->b - current_color_.b) / diff)
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
			If we're fading, increment by a step.
			The existence of step_count_ implies setNextColor() was called with fade = true.
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
