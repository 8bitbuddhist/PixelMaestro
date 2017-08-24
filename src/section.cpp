/*
	Section.cpp - Class for controlling multiple Pixels.
	Requires Pixel and Colors classes.
*/

#include "colors.h"
#include "pixel.h"
#include "section.h"
#include "utility.h"

namespace PixelMaestro {

	/**
	 * Constructor. Assigns Pixels to the Section.
	 * @param pixels Initial Pixel array.
	 * @param layout Initial layout (rows and columns) of the Pixels.
	 */
	Section::Section(Pixel *pixels, Point *layout) {
		setPixels(pixels, layout);
	}

	/**
	 * Returns the Section's active animation options.
	 * @return Active animation option.
	 */
	Section::AnimationOpts *Section::getAnimationOpts() {
		return &animation_opts_;
	}

	/**
	 * Returns the Section's Canvas.
	 * @return Section's Canvas.
	 */
	Canvas *Section::getCanvas() {
		return canvas_;
	}

	/**
		Returns the current color animation.

		@return Current color animation.
	*/
	Section::ColorAnimations Section::getColorAnimation() {
		return color_animation_;
	}

	/**
		Returns the amount of time between animation changes.

		@return speed The amount of time between animation changes.
	*/
	unsigned short Section::getCycleSpeed() {
		return cycle_interval_;
	}

	/**
		Returns the size of the Pixel grid.

		@return Size of the Pixel grid.
	*/
	Point *Section::getDimensions() {
		return dimensions_;
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
	unsigned int Section::getNumPixels() {
		return dimensions_->x * dimensions_->y;
	}

	/**
	 * Returns the Overlay (if one exists).
	 *
	 * @return Active Overlay.
	 */
	Section::Overlay *Section::getOverlay() {
		return overlay_;
	}

	/**
		Returns the Pixel at the specified index.

		@param pixel The index of the Pixel in the pixels_ array.
	*/
	Pixel *Section::getPixel(unsigned int pixel) {
		return &pixels_[pixel];
	}

	/**
		Returns the RGB value of the specified Pixel after applying post-processing effects.

		@param pixel Index of the Pixel.
		@return RGB value of the Pixel's de facto color.
	*/
	Colors::RGB Section::getPixelColor(unsigned int pixel) {
		if (overlay_ != nullptr) {
			return Colors::mixColors(getPixel(pixel)->getColor(), overlay_->section->getPixel(pixel)->getColor(), overlay_->mixMode, overlay_->alpha);
		}
		else {
			return *getPixel(pixel)->getColor();
		}
	}

	/**
		Returns the index of a Pixel given the row and column.

		@param row The row that the Pixel is in.
		@param column The column that the Pixel is in.
		@return The index of the Pixel.
	*/
	unsigned int Section::getPixelIndex(unsigned short row, unsigned short column) {
		return (row * dimensions_->x) + column;
	}

	/**
		Returns the Section's refresh rate.

		@return The refresh rate of the Section.
	*/
	unsigned short Section::getRefreshRate() {
		return refresh_interval_;
	}

	/**
		Sets all Pixels to the specified color.

		@param color New color.
	*/
	void Section::setAll(Colors::RGB *color) {
		for (unsigned int pixel = 0; pixel < getNumPixels(); pixel++) {
			setOne(pixel, color);
		}
	}

	/**
		Sets the Canvas to display.
		A Canvas is rendered on top of the ColorAnimation.

		@param canvas New Canvas.
		@param canvasCycleInterval The amount of time between frame changes in ms (defaults to 1000).
	*/
	void Section::setCanvas(Canvas *canvas) {
		canvas_ = canvas;
		canvas_->parent_section_ = this;
	}

	/**
		Changes the current color animation.

		@param animation Animation selection.
		@param reverseAnimation Whether to display the animation in reverse (only works for certain animations).
		@param orientation The orientation of the animation.
	*/
	void Section::setColorAnimation(ColorAnimations animation, bool reverseAnimation, AnimationOrientations orientation) {
		/*
		 * If the animation != NEXT, change to the animation.
		 * Otherwise, go to the next animation.
		 */
		if (animation) {
			color_animation_ = animation;
		}
		else {
			unsigned char animationNum = color_animation_ + 1;

			// If we've hit the last animation (NONE), cycle back to the first
			if (animationNum == Section::ColorAnimations::NONE) {
				animationNum = 1;
			}

			color_animation_ = ColorAnimations(animationNum);
		}

		// Handle any uninitialized options
		switch (animation) {
			case SPARKLE:
			{
				if (animation_opts_.sparkle_threshold == 255) {
					animation_opts_.sparkle_threshold = 60;
				}
				break;
			}
			default:
				break;
		}

		reverse_animation_ = reverseAnimation;
		animation_orientation_ = orientation;
	}

	/**
		Replaces the current color array.

		@param colors New color array.
		@param numColors Size of the array.
	*/
	void Section::setColors(Colors::RGB *colors, unsigned int numColors) {
		colors_ = colors;
		num_colors_ = numColors;
	}

	/**
		Jumps ahead to the specified point in the cycle.

		@param index Where the cycle should start.
	*/
	void Section::setCycleIndex(unsigned int index) {
		if (index > num_colors_) {
			cycle_index_ = (index - 1) % num_colors_;
		}
		else {
			cycle_index_ = index;
		}
	}

	/**
		Sets the speed between animation cycles.

		@param interval Rate in milliseconds between animation cycles.
		@param pause Specifies the amount of time to wait in milliseconds until the next animation cycle by speeding up the current cycle.
	*/
	void Section::setCycleInterval(unsigned short interval, unsigned short pause) {
		cycle_interval_ = interval;
		pause_ = pause;
	}

	/**
		Sets the specified Pixel to a new color.

		@param pixel The index of the Pixel to update.
		@param color New color.
	*/
	void Section::setOne(unsigned int pixel, Colors::RGB *color) {
		// Only continue if Pixel is within the bounds of the array.
		if (pixel < (unsigned int)(dimensions_->x * dimensions_->y)) {
			/*
				If pause is enabled, trick the Pixel into thinking the cycle is shorter than it is.
				This results in the Pixel finishing early and waiting until the next cycle.
			*/
			if (pause_ > 0) {
				getPixel(pixel)->setNextColor(color, fade_, cycle_interval_ - pause_, refresh_interval_);
			}
			else {
				getPixel(pixel)->setNextColor(color, fade_, cycle_interval_, refresh_interval_);
			}
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param row The row number of the Pixel.
		@param column The column number of the Pixel.
		@param color New color.
	*/
	void Section::setOne(unsigned short row, unsigned short column, Colors::RGB *color) {
		setOne(getPixelIndex(row, column), color);
	}

	/**
		Overlays another  Section on top of the current Section.
		You can retrieve the blended output by using getPixelColor() on the base Section.

		@param overlay The Overlay to set.
	*/
	void Section::setOverlay(Overlay *overlay) {
		overlay_ = overlay;
	}

	/**
		Sets the refresh rate of the Section (how quickly the Pixels update).

		@param interval Rate in milliseconds between Pixel redraws.
	*/
	void Section::setRefreshInterval(unsigned short interval) {
		refresh_interval_ = interval;
	}

	/**
		Toggles fading.
	*/
	void Section::toggleFade() {
		fade_ = !fade_;
	}

	/**
		Sets the Pixel array and layout used in the Section.

		@param pixels Pixel array.
		@param dimensions Dimensions of the Pixel array.
	*/
	void Section::setPixels(Pixel* pixels, Point *dimensions) {
		pixels_ = pixels;
		dimensions_ = dimensions;
	}

	/**
		Removes the overlay from the Section.
	*/
	void Section::unsetOverlay() {
		delete overlay_;
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Section::update(const unsigned long &currentTime) {

		// If this Section has an Overlay, update it.
		if (overlay_ != nullptr) {
			overlay_->section->update(currentTime);
		}

		if (currentTime - last_refresh_ >= (unsigned long)refresh_interval_) {

			/*
				Update the animation cycle.
				cycle_index_ tracks the Section's current position in the animation, while last_cycle_ tracks the time since the last position.
				If we've exceed our cycle time (indicated by speed_), calculate and move to the next animation position.
			*/
			if (currentTime - last_cycle_ >= (unsigned long)cycle_interval_) {

				// Determine which animation to run, then run it.
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
					default:
						setAll(&Colors::BLACK);
						break;
				}

				/*
				 * Check to see if we need to redraw the canvas.
				 */
				if (canvas_) {
					canvas_->update(currentTime);
				}

				// Update the last cycle time.
				last_cycle_ = currentTime;
			}

			/*
				Update each Pixel based on the last time the Section was refreshed.
			*/
			for (unsigned int pixel = 0; pixel < getNumPixels(); pixel++) {
				getPixel(pixel)->update();
			}

			// Update the last refresh time.
			last_refresh_ = currentTime;
		}
	}

	// Animation functions

	/// Flashes all Pixels on and off.
	void Section::animation_blink() {
		// Alternate the Pixel between its normal color and off (Colors::BLACK).
		if (cycle_index_ == 0) {
			for (unsigned short row = 0; row < dimensions_->y; row++) {
				for (unsigned short column = 0; column < dimensions_->x; column++) {
					setOne(row, column, &colors_[animation_getColorIndex(column)]);
				}
			}
		}
		else {
			setAll(&Colors::BLACK);
		}

		// Only run for two cycles.
		animation_updateCycle(0, 2);
	}

	/// Cycles all Pixels through all stored colors.
	void Section::animation_cycle() {
		setAll(&colors_[cycle_index_]);
		animation_updateCycle(0, num_colors_);
	}

	/**
		Calculates the index of a color.
		Used mainly to determine which color a Pixel should use during an animation based on where it is in the array.
		For example, this allows a Section of 10 Pixels to use an array of 5 colors by repeating the colors after Pixel 5.

		@param count Number to resolve to an index.
		@return Resulting index.
	*/
	unsigned int Section::animation_getColorIndex(unsigned int count) {
		if (num_colors_ > 0 && count >= num_colors_) {
			count %= num_colors_;
		}

		return count;
	}

	/**
		Converges colors into the center of the Section.

		Supports vertical orientation
	*/
	void Section::animation_merge() {

		// Calculate the center of the array
		unsigned short midPoint;
		unsigned short count;

		if (animation_orientation_ == VERTICAL) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				midPoint = (dimensions_->y / 2) - 1;
				count = 0;

				// Note: column *HAS* TO BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int row = midPoint; row >= 0; row--) {
					setOne(row, column, &colors_[animation_getColorIndex(count + cycle_index_)]);
					count++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (getNumPixels() % 2 != 0) {
					midPoint += 1;
					setOne(midPoint, column, &colors_[cycle_index_]);
				}

				midPoint += 1;

				// Go from the center to the last
				count = 0;
				for (short row = midPoint; row < dimensions_->y; row++) {
					setOne(row, column, &colors_[animation_getColorIndex(count + cycle_index_)]);
					count++;
				}
			}
		}
		else {	// Horizontal
			for (unsigned short row = 0; row < dimensions_->y; row++) {
				midPoint = (dimensions_->x / 2) - 1;
				count = 0;

				// Note: column *HAS* TO BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int column = midPoint; column >= 0; column--) {
					setOne(row, column, &colors_[animation_getColorIndex(count + cycle_index_)]);
					count++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (getNumPixels() % 2 != 0) {
					midPoint += 1;
					setOne(row, midPoint, &colors_[cycle_index_]);
				}

				midPoint += 1;

				// Go from the center to the last
				count = 0;
				for (short column = midPoint; column < dimensions_->x; column++) {
					setOne(row, column, &colors_[animation_getColorIndex(count + cycle_index_)]);
					count++;
				}
			}
		}

		animation_updateCycle(0, num_colors_);
	}

	/**
		Cycles colors back and forth in a ping-pong pattern.

		Supports vertical orientation
	*/
	void Section::animation_pong() {
		for (unsigned short row = 0; row < dimensions_->y; row++) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				if (animation_orientation_ == VERTICAL) {
					setOne(row, column, &colors_[animation_getColorIndex(row + cycle_index_)]);
				}
				else {	// Horizontal
					setOne(row, column, &colors_[animation_getColorIndex(column + cycle_index_)]);
				}
			}
		}

		if (cycle_index_ == 0) {
			// Start ping
			reverse_animation_ = false;
		}
		if (cycle_index_ == num_colors_ - 1) {
			// Start pong
			reverse_animation_ = true;
		}

		animation_updateCycle(0, num_colors_);
	}

	/// Sets each Pixel to a random stored color .
	void Section::animation_randomIndex() {
		for (unsigned int pixel = 0; pixel < getNumPixels(); pixel++) {
			setOne(pixel, &colors_[Utility::rand() % num_colors_]);
		}
	}

	/// Sets each Pixel to a solid color.
	void Section::animation_solid() {
		for (unsigned short row = 0; row < dimensions_->y; row++) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				setOne(row, column, &colors_[animation_getColorIndex(column)]);
			}
		}
	}

	/// Creates a shimmering effect by activating random Pixels.
	void Section::animation_sparkle() {
		for (short row = 0; row < dimensions_->y; row++) {
			for (short column = 0; column < dimensions_->x; column++) {
				if ((Utility::rand() % 100) > animation_opts_.sparkle_threshold) {
					setOne(row, column, &colors_[animation_getColorIndex(column)]);
				}
				else {
					setOne(row, column, &Colors::BLACK);
				}
			}
		}
	}

	/**
		Updates the current cycle.
		If reverse_animation_ is true, this will automatically reverse the animation.
		@param min The minimum value of the cycle.
		@param max The maximum value of the cycle.
	*/
	void Section::animation_updateCycle(unsigned int min, unsigned int max) {
		last_cycle_ = last_refresh_;
		if (reverse_animation_) {
			cycle_index_--;
			if ((cycle_index_ + 1) == 0) {	// I know, buffer overflows are ugly, but in this case it works.
				cycle_index_ = max - 1;
			}
		}
		else {
			cycle_index_++;
			if (cycle_index_ >= max) {
				cycle_index_ = min;
			}
		}
	}

	/**
		Creates a wave effect by scrolling the color array across the Section.

		Vertical orientation
	*/
	void Section::animation_wave() {
		for (unsigned short row = 0; row < dimensions_->y; row++) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				if (animation_orientation_ == VERTICAL) {
					setOne(row, column, &colors_[animation_getColorIndex(row + cycle_index_)]);
				}
				else {	// Horizontal
					setOne(row, column, &colors_[animation_getColorIndex(column + cycle_index_)]);
				}
			}
		}


		animation_updateCycle(0, num_colors_);
	}
}
