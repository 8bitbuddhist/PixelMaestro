/*
	Section.cpp - Class for controlling multiple Pixels.
	Requires Pixel and Colors classes.
*/

#include <limits.h>
#include <stdlib.h>
#include "Colors.h"
#include "Pixel.h"
#include "Section.h"

namespace PixelMaestro {
	/**
		Default constructor.
		Note that if you use the default constructor, you MUST use setPixels() to initialize the Pixel array.
	*/
    Section::Section() {}

	/**
		Constructor. A Section is a collection of initialized Pixels.

		@param pixels Initial Pixel array.
		@param numPixels Number of Pixels.
	*/
	Section::Section(Pixel *pixels, unsigned char numPixels) {
        setPixels(pixels, numPixels);
	}

	/**
		Returns whether the Section is fading.

		@return Whether the Section is fading.
	*/
	bool Section::getFade() {
		return fade_;
	}

	/**
		Returns the number of Pixels in the Section.

		@return Number of Pixels.
	*/
	unsigned char Section::getNumPixels() {
		return num_pixels_;
	}

	/**
		Returns the Pixel at the specified index.
		Useful for getting the color of the Pixel for display via pixel->getColor().

		@param pixel Index of the Pixel.
		@return Pixel Reference to Pixel.
	*/
	Pixel *Section::getPixel(unsigned char pixel) {
		return &pixels_[pixel];
	}

	/**
		Returns the speed of the array.

		@return speed The current speed.
	*/
	unsigned char Section::getUpdateSpeed() {
		return speed_;
	}

	/**
		Returns the current color animation.

		@return Current color animation.
	*/
	Section::ColorAnimations Section::getColorAnimation() {
		return color_animation_;
	}

	/**
		Sets all Pixels to the specified color.

		@param color New color.
	*/
	void Section::setAll(Colors::RGB *color) {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			setOne(pixel, color);
		}
	}

	/**
		Changes the current color animation.

		@param animation Animation selection.
		@param reverseAnimation Whether to display the animation in reverse (only works for certain animations).
	*/
	void Section::setColorAnimation(ColorAnimations animation, bool reverseAnimation) {
		// If animation was supplied, change to the desired animation.
		// Otherwise, increment the current animation to the next one.
		if (animation) {
			color_animation_ = animation;
		}
		else {
			unsigned char animationNum = color_animation_ + 1;

			if (animationNum > Section::ColorAnimations::PATTERN) {
				animationNum = Section::ColorAnimations::SOLID;
			}

			color_animation_ = ColorAnimations(animationNum);
		}

		reverse_animation_ = reverseAnimation;

		// TODO: Verify whether PONG *needs* cycle_index_ be reset to 0
	}

	/**
		Replaces the current color array.

		@param colors New color array.
		@param numColors Size of the array.
	*/
	void Section::setColors(Colors::RGB *colors, unsigned char numColors) {
		colors_ = colors;
		num_colors_ = numColors;
	}

	/**
		Jumps ahead to the specified point in the cycle.

		@param index Where the cycle should start.
	*/
	void Section::setCycleIndex(unsigned char index) {
		if (index > num_colors_) {
			cycle_index_ = (index - 1) % num_colors_;
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
	void Section::setOne(unsigned char pixel, Colors::RGB *color) {
		pixels_[pixel].setNextColor(color, fade_, speed_);
	}

	/**
		Changes the display pattern.

		@param pattern Pointer to the pattern (byte) array.
		@param patternLength Length of the pattern array.
	*/
	void Section::setPattern(unsigned char *pattern, unsigned char patternLength) {
		pattern_ = pattern;
		pattern_length_ = patternLength;
	}

	/**
        Changes the Pixel group used in the Section.

        @param pixels Initial Pixel array.
		@param numPixels Number of Pixels.
	*/
	void Section::setPixels(Pixel* pixels, unsigned char numPixels) {
        pixels_ = pixels;
		num_pixels_ = numPixels;
	}

	/**
		Sets the update speed in milliseconds.

		@param speed Delay between individual animation steps.
		@param delay Delay between complete animation cycles.
	*/
	void Section::setUpdateSpeed(unsigned char speed, unsigned char delay) {
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
	void Section::toggleFade() {
		fade_ = !fade_;
		if (fade_) {
			speed_ /= speed_;
		}
		else {
			speed_ *= speed_;
		}
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Section::update(unsigned long currentTime) {
		// Update the timer
		current_time_ = &currentTime;

		/*
			Run if either of the following cases is true:
				1. The Section has never updated (last_time_ == 0).
				2. The program's runtime minus the Section's last update time exceeds the update interval (current_time_ - last_time_ >= speed).
		*/
		if ((last_time_ == 0) || (*current_time_ - last_time_ >= speed_)) {

			// Determine which animation to run, then run the associated method.
			// Defaults to off.
			switch (color_animation_) {
				case Section::ColorAnimations::SOLID:
					animation_solid();
					break;
				case Section::ColorAnimations::BLINK:
					animation_blink();
					break;
				case Section::ColorAnimations::CYCLE:
					animation_cycle();
					break;
				case Section::ColorAnimations::WAVE:
					animation_wave();
					break;
				case Section::ColorAnimations::MERGE:
					animation_merge();
					break;
				case Section::ColorAnimations::PONG:
					animation_pong();
					break;
				case Section::ColorAnimations::SPARKLE:
					animation_sparkle();
					break;
				case Section::ColorAnimations::RANDOMINDEX:
					animation_randomIndex();
					break;
				case Section::ColorAnimations::PATTERN:
					animation_pattern();
					break;
				case Section::ColorAnimations::STATIC:
					animation_static();
					break;
				default:
					setAll(&Colors::BLACK);
					break;
			}

			// Update each LED.
			for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
				pixels_[pixel].update();
			}

			// Update the timer.
			last_time_ = *current_time_;
		}
	}

	// Private animation functions

	/**
		Creates a blinking effect.

		Modes: BLINK
	*/
	void Section::animation_blink() {
		// Alternate the Pixel between its normal color and off (Colors::BLACK).
		if (cycle_index_ == 0) {
			for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
				setOne(pixel, &colors_[animation_getColorIndex(pixel)]);
			}
		}
		else {
			setAll(&Colors::BLACK);
		}
		animation_incrementCycle();

		// Only run for two cycles.
		if (cycle_index_ == 2) {
			cycle_index_ = 0;
		}
	}

	/**
		Cycles all Pixels through all stored colors.

		Modes: CYCLE
	*/
	void Section::animation_cycle() {
		setAll(&colors_[cycle_index_]);

		if (reverse_animation_) {
			animation_decrementCycle();
		}
		else {
			animation_incrementCycle();
		}
	}

	/**
		Calculates the index of a color.
		Used mainly to determine which color a Pixel should use during an animation based on where it is in the array.
		For example, this allows a Section of 10 Pixels to use an array of 5 colors by repeating the colors after Pixel 5.

		@param count Number to resolve to an index.
		@return Resulting index.
	*/
	unsigned char Section::animation_getColorIndex(unsigned char count) {
		if (count >= num_colors_) {
			count %= num_colors_;
		}

		return count;
	}

	/**
		Decrements the current position in the cycle.
	*/
	void Section::animation_decrementCycle() {
		// Only continue if the Pixels are finished cycling through their steps.
		if ((pixels_[0].getStepCount() == 0) && (*current_time_ - cycle_end_ >= delay_)) {
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
	void Section::animation_incrementCycle() {
		// Only continue if the Pixels are finished cycling through their steps.
		if ((pixels_[0].getStepCount() == 0) && (*current_time_ - cycle_end_ >= delay_)) {
			cycle_end_ = *current_time_;
			cycle_index_++;
			if (cycle_index_ >= num_colors_) {
				cycle_index_ = 0;
			}
		}
	}

	/**
		Creates an effect where colors converge into the center of the array.

		Modes: MERGE
	*/
	void Section::animation_merge() {

		// Calculate the center of the array
		unsigned char midPoint = (num_pixels_ / 2) - 1;
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
		If there is no pattern set, blink.

		Modes: PATTERN
	*/
	void Section::animation_pattern() {
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
	void Section::animation_pong() {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			setOne(pixel, &colors_[animation_getColorIndex(pixel + cycle_index_)]);
		}

		if (cycle_index_ == 0) {
			reverse_animation_ = false;		// Start upcycle
		}
		if (cycle_index_ == num_colors_ - 1) {
			reverse_animation_ = true;		// Start downcycle
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
	void Section::animation_randomIndex() {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			if (pixels_[pixel].getColor() == pixels_[pixel].getNextColor()) {
				setOne(pixel, &colors_[rand() % num_colors_]);
			}
		}
	}

	/**
		Sets each Pixel to a solid color.

		Modes: SOLID
	*/
	void Section::animation_solid() {
		for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
			setOne(pixel, &colors_[animation_getColorIndex(pixel)]);
		}
	}

	/**
		Creates a shimmering effect by turning on random Pixels.

		Modes: SPARKLE
	*/
	void Section::animation_sparkle() {
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
		Creates a static effect by blending each Pixel between varying levels of gray.

		Modes: STATIC
	*/
	void Section::animation_static() {
			for (unsigned char pixel = 0; pixel < num_pixels_; pixel++) {
				colors_[pixel] = Colors::mixColors(&Colors::BLACK, &Colors::WHITE, Colors::MixMode::ALPHA_BLENDING, 0.0 + (rand() / ( RAND_MAX / (0.5) ) ));
				setOne(pixel, &colors_[pixel]);
				//setOne(led, &colors_[animation_getColorIndex(led)]);
			}
	}

	/**
		Creates a wave effect by scrolling the color array across the Section.

		Modes: WAVE
	*/
	void Section::animation_wave() {
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