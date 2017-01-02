/*
	Line.cpp - Library for controlling multiple RGB pixels
	Requires Pixel and Colors libraries

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

#include <limits.h>
#include <stdlib.h>
#include "Colors.h"
#include "Line.h"
#include "Pixel.h"

namespace PixelMaestro {
    Line::Line() {}

	/**
		Constructor. Initializes the Pixel array.
		Note that if you use the empty constructor, you MUST use setPixels().

		@param pixels Initial pixel array.
		@param numPixels Number of pixels.
	*/
	Line::Line(Pixel *pixels, unsigned char numPixels) {
        setPixels(pixels, numPixels);
	}

	/**
		Returns the current time as stored by the strip.

		@return Current time.
	*/
	unsigned long Line::getCurrentTime() {
		return *current_time_;
	}

	/**
		Returns whether the Line is fading.
		@return Line is fading.
	*/
	bool Line::getFade() {
		return fade_;
	}

	/**
		Returns the Pixel at the specified index.
		Useful for getting the color of the Pixel for display via pixel->getColor().

		@param pixel Index of the Pixel.
		@return Pixel Reference to Pixel.
	*/
	Pixel *Line::getPixel(unsigned char pixel) {
		return &pixels_[pixel];
	}

	/**
		Returns the current color animation.

		@return Current Line::ColorAnimation.
	*/
	Line::ColorAnimations Line::getColorAnimation() {
		return color_animation_;
	}

	/**
		Sets all Pixelss to the specified color.

		@param color New color.
	*/
	void Line::setAll(Colors::RGB *color) {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			setOne(pixel, color);
		}
	}

	/**
		Changes the current color animation.

		@param animation Animation selection.
		@param reverseAnimation Whether to display the animation in reverse (only works for certain animations).
	*/
	void Line::setColorAnimation(ColorAnimations animation, bool reverseAnimation) {
		// If animation was supplied, change to the desired animation.
		// Otherwise, increment the current animation to the next one.
		if (animation) {
			color_animation_ = animation;
		}
		else {
			unsigned char animationNum = color_animation_ + 1;

			if (animationNum > Line::ColorAnimations::PATTERN) {
				animationNum = Line::ColorAnimations::SOLID;
			}

			color_animation_ = ColorAnimations(animationNum);
		}

		reverse_animation_ = reverseAnimation;

		// TODO: Verify whether PONG *needs* cycle_index_ be reset to 0
	}

	/**
		Replaces the current colors_ array with a new array.

		@param colors New color array.
		@param numColors Size of the array.
	*/
	void Line::setColors(Colors::RGB *colors, unsigned char numColors) {
		colors_ = colors;
		num_colors_ = numColors;
	}

	/**
		Jumps ahead to the specified point in the cycle.

		@param index Where the cycle should start.
	*/
	void Line::setCycleIndex(unsigned char index) {
		if (index > cycle_index_) {
			cycle_index_ %= index;
		}
		else {
			cycle_index_ = index;
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param pixel Pixel to change.
		@param color New color.
	*/
	void Line::setOne(unsigned char pixel, Colors::RGB *color) {
		pixels_[pixel].setNextColor(color, fade_, speed_);
	}

	/**
		Sets the pattern to be displayed.

		@param pattern Pointer to the unsigned char array where the lines are stored.
		@param patternLength Length of the pattern array.
	*/
	void Line::setPattern(unsigned char *pattern, unsigned char patternLength) {
		pattern_ = pattern;
		pattern_length_ = patternLength;
	}

	/**
        Sets the pixels used in the array.

        @param pixels Initial pixel array.
		@param numPixels Number of pixels.
	*/
	void Line::setPixels(Pixel* pixels, unsigned char numPixels) {
        pixels_ = pixels;
		num_pixels_ = numPixels;
	}

	/**
		Sets the update speed in milliseconds.

		@param speed Delay between individual animation steps.
		@param delay Delay between complete animation cycles.
	*/
	void Line::setUpdateSpeed(unsigned char speed, unsigned char delay) {
		delay_ = delay;
		// If not fading, increase the delay so the array doesn't update as rapidly.
		if (fade_) {
			speed_ = speed;
		}
		else {
			speed_ = speed * speed;
		}
	}

	/**
		Toggles fading. We need to adjust the speed when fading vs. not fading.
	*/
	void Line::toggleFade() {
		fade_ = !fade_;
		if (fade_) {
			speed_ /= speed_;
		}
		else {
			speed_ *= speed_;
		}
	}

	/**
		Main update routine. Must be called in loop().
	*/
	void Line::update(unsigned long currentTime) {
		// Update the timer
		//current_time_ = millis();
		current_time_ = &currentTime;
		if ((last_time_ == 0) || (*current_time_ - last_time_ >= speed_)) {

			// Run a function based on the current mode.
			// Defaults to Modes::NONE
			switch (color_animation_) {
				case Line::ColorAnimations::SOLID:
					animation_solid();
					break;
				case Line::ColorAnimations::BLINK:
					animation_blink();
					break;
				case Line::ColorAnimations::CYCLE:
					animation_cycle();
					break;
				case Line::ColorAnimations::WAVE:
					animation_wave();
					break;
				case Line::ColorAnimations::MERGE:
					animation_merge();
					break;
				case Line::ColorAnimations::PONG:
					animation_pong();
					break;
				case Line::ColorAnimations::SPARKLE:
					animation_sparkle();
					break;
				case Line::ColorAnimations::RANDOMINDEX:
					animation_randomIndex();
					break;
				case Line::ColorAnimations::PATTERN:
					animation_pattern();
					break;
				case Line::ColorAnimations::STATIC:
					animation_static();
					break;
				default:
					setAll(&Colors::BLACK);
					break;
			}

			// Update each LED
			for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
				pixels_[pixel].update();
			}

			// Update the timer
			last_time_ = *current_time_;
		}
	}

	// Private functions

	/**
		Creates a blinking effect.

		Modes: BLINK
	*/
	void Line::animation_blink() {
		if (cycle_index_ == 0) {
			for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
				setOne(pixel, &colors_[animation_getColorIndex(pixel)]);
			}
		}
		else {
			setAll(&Colors::BLACK);
		}
		animation_incrementCycle();

		if (cycle_index_ == 2) {
			cycle_index_ = 0;
		}
	}

	/**
		Cycles through the colors stored in colors_.

		Modes: CYCLE
	*/
	void Line::animation_cycle() {
		setAll(&colors_[cycle_index_]);

		if (reverse_animation_) {
			animation_decrementCycle();
		}
		else {
			animation_incrementCycle();
		}
	}

	/**
		Gets the current color index.
		Used to detect the current position in a cycle.

		@param count Index used by the calling function, if any.
		@return Current index.
	*/
	unsigned char Line::animation_getColorIndex(unsigned char count) {
		if (count >= num_colors_) {
			count %= num_colors_;
		}

		return count;
	}

	/**
		Decrements the current position in the cycle.
	*/
	void Line::animation_decrementCycle() {
		// If the Pixels are finished cycling through their steps, continue.
		if ((pixels_[0].getStepCount() == 0) && (*current_time_ - cycle_end_ >= delay_)) {
			//cycle_end_ = millis();
			cycle_end_ = *current_time_;
			cycle_index_--;
			if (cycle_index_ < 0) {
				cycle_index_ = num_colors_ - 1;
			}
		}
	}

	/**
		Increments the current position in the cycle.
	*/
	void Line::animation_incrementCycle() {
		// If the Pixels are finished cycling through their steps, continue.
		if ((pixels_[0].getStepCount() == 0) && (*current_time_ - cycle_end_ >= delay_)) {
			//cycle_end_ = millis();
			cycle_end_ = *current_time_;
			cycle_index_++;
			if (cycle_index_ >= num_colors_) {
				cycle_index_ = 0;
			}
		}
	}

	/**
		Creates a converging effect.

		Modes: MERGE
	*/
	void Line::animation_merge() {
		unsigned char midPoint = (num_pixels_ / 2) - 1;

		// Go from the center to the first
		unsigned char count = 0;

		for (int pixel = midPoint; pixel >= 0; pixel--) {
			setOne(pixel, &colors_[animation_getColorIndex(count + cycle_index_)]);
			count++;
		}

		// Check for an odd number of Pixels.
		// If so, set the center one to index 0.
		if (num_pixels_ % 2 != 0) {
			midPoint += 1;
			setOne(midPoint, &colors_[cycle_index_]);
		}

		midPoint += 1;

		// Go from the center to the last
		count = 0;
		for (int pixel = midPoint; pixel < num_pixels_; pixel++) {
			setOne(pixel, &colors_[animation_getColorIndex(count + cycle_index_)]);
			count++;
		}

		if (reverse_animation_) {
			animation_decrementCycle();
		}
		else {
			animation_incrementCycle();
		}
	}

	/**
		Scrolls through the pattern stored in pattern_.

		Modes: PATTERN
	*/
	void Line::animation_pattern() {
		if (!(pattern_ && pattern_length_)) {
			animation_blink();
			return;
		}

		// Increment through each bit. If the bit is set, turn on the Pixel.
		unsigned char data = pattern_[cycle_index_];
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			if (data & (1 << pixel)) {
				setOne(pixel, &colors_[animation_getColorIndex(pixel)]);
			}
			else {
				setOne(pixel, &Colors::BLACK);
			}
		}

		cycle_index_++;
		if (cycle_index_ > pattern_length_) {
			cycle_index_ = 0;
		}
	}

	/**
		Cycles colors back and forth in a ping-pong pattern.

		Modes: PONG
	*/
	void Line::animation_pong() {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			setOne(pixel, &colors_[animation_getColorIndex(pixel + cycle_index_)]);
		}

		if (cycle_index_ == 0) {
			reverse_animation_ = false;		// start upcycle
		}
		if (cycle_index_ == num_colors_ - 1) {
			reverse_animation_ = true;		// start downcycle
		}

		if (reverse_animation_) {
			animation_decrementCycle();
		}
		else {
			animation_incrementCycle();
		}
	}

	/**
		Sets each Pixel to a random color stored in colors_.

		Modes: RANDOMINDEX
	*/
	void Line::animation_randomIndex() {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			if (Colors::colorsMatch(pixels_[pixel].getColor(), pixels_[pixel].getNextColor())) {
				setOne(pixel, &colors_[rand() % num_colors_]);
			}
		}
	}

	/**
		Sets each Pixel to a solid color.

		Modes: SOLID
	*/
	void Line::animation_solid() {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			setOne(pixel, &colors_[animation_getColorIndex(pixel)]);
		}
	}

	/**
		Creates a shimmering effect.
		A default color can be used in place of colors_[led].

		Modes: SPARKLE
	*/
	void Line::animation_sparkle() {
		unsigned char activePixel = rand() % num_pixels_;

		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			if (pixel == activePixel) {
				setOne(pixel, &colors_[animation_getColorIndex(pixel)]);
			}
			else {
				setOne(pixel, &Colors::BLACK);
			}
		}
	}

	/**
		Creates a static effect.

		Modes: STATIC
	*/
	void Line::animation_static() {
			for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
				colors_[pixel] = Colors::mixColors(&Colors::BLACK, &Colors::WHITE, Colors::MixMode::ALPHA_BLENDING, 0.0 + (rand() / ( RAND_MAX / (0.5) ) ));
				setOne(pixel, &colors_[pixel]);
				//setOne(led, &colors_[animation_getColorIndex(led)]);
			}
	}

	/**
		Creates a wave effect.

		Modes: WAVE
	*/
	void Line::animation_wave() {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			setOne(pixel, &colors_[animation_getColorIndex(pixel + cycle_index_)]);
		}

		if (reverse_animation_) {
			animation_decrementCycle();
		}
		else {
			animation_incrementCycle();
		}
	}
}
