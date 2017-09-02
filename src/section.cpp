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
	Section::Section(Pixel* pixels, Point* layout) {
		set_pixels(pixels, layout);
	}

	/**
	 * Returns the Section's active animation options.
	 * @return Active animation option.
	 */
	Section::AnimationOpts *Section::get_animation_opts() {
		return &animation_opts_;
	}

	/**
	 * Returns the Section's Canvas.
	 * @return Section's Canvas.
	 */
	Canvas* Section::get_canvas() {
		return canvas_;
	}

	/**
		Returns the current color animation.

		@return Current color animation.
	*/
	Section::ColorAnimations Section::get_color_animation() {
		return color_animation_;
	}

	/**
		Returns the amount of time between animation changes.

		@return speed The amount of time between animation changes.
	*/
	unsigned short Section::get_cycle_interval() {
		return cycle_interval_;
	}

	/**
		Returns the size of the Pixel grid.

		@return Size of the Pixel grid.
	*/
	Point* Section::get_dimensions() {
		return dimensions_;
	}

	/**
		Returns whether the Section is fading.

		@return Whether the Section is fading.
	*/
	bool Section::get_fade() {
		return fade_;
	}

	/**
		Returns the number of Pixels in the Section.

		@return Number of Pixels.
	*/
	unsigned int Section::get_num_pixels() {
		return dimensions_->x * dimensions_->y;
	}

	/**
	 * Returns the Overlay (if one exists).
	 *
	 * @return Active Overlay.
	 */
	Section::Overlay* Section::get_overlay() {
		return overlay_;
	}

	/**
		Returns the Pixel at the specified index.

		@param pixel The index of the Pixel in the pixels_ array.
	*/
	Pixel* Section::get_pixel(unsigned int pixel) {
		return &pixels_[pixel];
	}

	/**
		Returns the final color of the specified Pixel after applying post-processing effects (e.g. Overlays).

		@param pixel Index of the Pixel.
		@return RGB value of the Pixel's final color.
	*/
	Colors::RGB Section::get_pixel_color(unsigned int pixel) {
		if (overlay_ != nullptr) {
			return Colors::mix_colors(get_pixel(pixel)->get_color(), overlay_->section->get_pixel(pixel)->get_color(), overlay_->mix_mode, overlay_->alpha);
		}
		else {
			return *get_pixel(pixel)->get_color();
		}
	}

	/**
	 * Returns the index of a Pixel given the Pixel's Point.
	 * @param coordinates The Pixel's Point.
	 * @return The index of the Pixel.
	 */
	unsigned int Section::get_pixel_index(Point* coordinates) {
		return get_pixel_index(coordinates->x, coordinates->y);
	}

	/**
		Returns the index of a Pixel given the x and y-coordinates.

		@param x The Pixel's x-coordinate.
		@param y The Pixel's y-coordinate.
		@return The index of the Pixel.
	*/
	unsigned int Section::get_pixel_index(unsigned short x, unsigned short y) {
		return (y * dimensions_->x) + x;
	}

	/**
		Returns the Section's refresh rate.

		@return The refresh rate of the Section.
	*/
	unsigned short Section::get_refresh_interval() {
		return refresh_interval_;
	}

	/**
		Sets all Pixels to the specified color.

		@param color New color.
	*/
	void Section::set_all(Colors::RGB* color) {
		for (unsigned int pixel = 0; pixel < get_num_pixels(); pixel++) {
			set_one(pixel, color);
		}
	}

	/**
		Sets the Canvas to display.
		Also sets the Canvas' parent Section to the current Section.

		@param canvas New Canvas.
	*/
	void Section::set_canvas(Canvas* canvas) {
		canvas_ = canvas;
		canvas_->parent_section = this;
	}

	/**
		Changes the current color animation.

		@param animation Animation selection.
		@param reverse_animation Whether to display the animation in reverse (only works for certain animations).
		@param orientation The orientation of the animation.
	*/
	void Section::set_color_animation(ColorAnimations animation, bool reverse_animation, AnimationOrientations orientation, AnimationOpts* opts) {
		/*
		 * If the animation != NEXT, change to the animation.
		 * Otherwise, go to the next animation.
		 */
		if (animation != ColorAnimations::NEXT) {
			color_animation_ = animation;
		}
		else {
			unsigned char animationNum = color_animation_ + 1;

			// If we've hit the last animation (NONE), cycle back to the first
			if (animationNum == ColorAnimations::NONE) {
				animationNum = 1;
			}

			color_animation_ = ColorAnimations(animationNum);
		}

		// Handle any uninitialized options
		switch (animation) {
			case SPARKLE:
			{
				if (opts != nullptr && opts->sparkle_threshold) {
					animation_opts_.sparkle_threshold = opts->sparkle_threshold;
				}
				else {
					animation_opts_.sparkle_threshold = 60;
				}
				break;
			}
			default:
				break;
		}

		reverse_animation_ = reverse_animation;
		animation_orientation_ = orientation;
	}

	/**
		Replaces the current color array.

		@param colors New color array.
		@param num_colors Size of the array.
	*/
	void Section::set_colors(Colors::RGB* colors, unsigned short num_colors) {
		colors_ = colors;
		num_colors_ = num_colors;
	}

	/**
		Jumps ahead to the specified point in the cycle.

		@param index Where the cycle should start.
	*/
	void Section::set_cycle_index(unsigned short index) {
		if (index > num_colors_) {
			cycle_index_ = (index - 1) % num_colors_;
		}
		else {
			cycle_index_ = index;
		}
	}

	/**
		Sets the speed between animation cycles.

		@param interval Time between animation cycles (in milliseconds).
		@param pause Time to delay the start of the transition to the next animation (in ms).
	*/
	void Section::set_cycle_interval(unsigned short interval, unsigned short pause) {
		cycle_interval_ = interval;
		pause_ = pause;
	}

	/**
		Sets the specified Pixel to a new color.

		@param pixel The index of the Pixel to update.
		@param color New color.
	*/
	void Section::set_one(unsigned int pixel, Colors::RGB* color) {
		// Only continue if Pixel is within the bounds of the array.
		if (pixel < get_num_pixels()) {
			/*
				If pause is enabled, trick the Pixel into thinking the cycle is shorter than it is.
				This results in the Pixel finishing early and waiting until the next cycle.
			*/
			if (pause_ > 0) {
				get_pixel(pixel)->set_next_color(color, fade_, cycle_interval_ - pause_, refresh_interval_);
			}
			else {
				get_pixel(pixel)->set_next_color(color, fade_, cycle_interval_, refresh_interval_);
			}
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param row The row number of the Pixel.
		@param column The column number of the Pixel.
		@param color New color.
	*/
	void Section::set_one(unsigned short row, unsigned short column, Colors::RGB* color) {
		set_one(get_pixel_index(column, row), color);
	}

	/**
		Overlays another  Section on top of the current Section.
		You can retrieve the blended output by using get_pixel_color() on the base Section.

		@param overlay The Overlay to set.
	*/
	void Section::set_overlay(Overlay* overlay) {
		overlay_ = overlay;
	}

	/**
		Sets the refresh rate of the Section (how quickly the Pixels update).

		@param interval Rate in milliseconds between Pixel redraws.
	*/
	void Section::set_refresh_interval(unsigned short interval) {
		refresh_interval_ = interval;
	}

	/**
		Toggles fading.
	*/
	void Section::toggle_fade() {
		fade_ = !fade_;
	}

	/**
		Sets the Pixel array and layout used in the Section.

		@param pixels Pixel array.
		@param dimensions Dimensions of the Pixel array.
	*/
	void Section::set_pixels(Pixel* pixels, Point* dimensions) {
		pixels_ = pixels;
		dimensions_ = dimensions;
	}

	/**
		Removes the overlay from the Section.
	*/
	void Section::unset_overlay() {
		overlay_ = nullptr;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Section::update(const unsigned long& current_time) {

		// If this Section has an Overlay, update it.
		if (overlay_ != nullptr) {
			overlay_->section->update(current_time);
		}

		if (current_time - last_refresh_ >= (unsigned long)refresh_interval_) {

			/*
				Update the animation cycle.
				cycle_index_ tracks the Section's current position in the animation, while last_cycle_ tracks the time since the last position.
				If we've exceed our cycle time (indicated by speed_), calculate and move to the next animation position.
			*/
			if (current_time - last_cycle_ >= (unsigned long)cycle_interval_) {

				// Determine which animation to run, then run it.
				// Defaults to off.
				switch (color_animation_) {
					case ColorAnimations::NEXT:
						break;
					case ColorAnimations::SOLID:
						animation_solid();
						break;
					case ColorAnimations::BLINK:
						animation_blink();
						break;
					case ColorAnimations::CYCLE:
						animation_cycle();
						break;
					case ColorAnimations::WAVE:
						animation_wave();
						break;
					case ColorAnimations::PONG:
						animation_pong();
						break;
					case ColorAnimations::MERGE:
						animation_merge();
						break;
					case ColorAnimations::RANDOM:
						animation_random();
						break;
					case ColorAnimations::SPARKLE:
						animation_sparkle();
						break;
					default:
						set_all(&Colors::BLACK);
						break;
				}

				/*
				 * Check to see if we need to redraw the canvas.
				 */
				if (canvas_ != nullptr) {
					canvas_->update(current_time);
				}

				// Update the last cycle time.
				last_cycle_ = current_time;
			}

			/*
				Update each Pixel based on the last time the Section was refreshed.
			*/
			for (unsigned short pixel = 0; pixel < get_num_pixels(); pixel++) {
				get_pixel(pixel)->update();
			}

			// Update the last refresh time.
			last_refresh_ = current_time;
		}
	}

	// Animation functions

	/// Flashes all Pixels on and off.
	void Section::animation_blink() {
		// Alternate the Pixel between its normal color and off (Colors::BLACK).
		if (cycle_index_ == 0) {
			for (unsigned short row = 0; row < dimensions_->y; row++) {
				for (unsigned short column = 0; column < dimensions_->x; column++) {
					set_one(row, column, &colors_[animation_get_color_index(column)]);
				}
			}
		}
		else {
			set_all(&Colors::BLACK);
		}

		// Only run for two cycles.
		animation_update_cycle(0, 2);
	}

	/// Cycles all Pixels through all stored colors.
	void Section::animation_cycle() {
		set_all(&colors_[cycle_index_]);
		animation_update_cycle(0, num_colors_);
	}

	/**
		Calculates the index of a color.
		Used mainly to determine which color a Pixel should use during an animation based on where it is in the array.
		For example, if the Section has 10 Pixels and 5 Colors, the Pixel at index 7 (count) will use the Color at index 2 (7 % 5 == 2).

		@param count Number to resolve to an index.
		@return Resulting index.
	*/
	unsigned short Section::animation_get_color_index(unsigned short count) {
		if (num_colors_ > 0 && count >= num_colors_) {
			count %= num_colors_;
		}

		return count;
	}

	/**
		Converges colors into the center of the Section.

		Supports vertical orientation.
	*/
	void Section::animation_merge() {

		// Store the center of the array and the current Pixel index.
		unsigned short mid_point, count;

		if (animation_orientation_ == VERTICAL) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				mid_point = (dimensions_->y / 2) - 1;
				count = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int row = mid_point; row >= 0; row--) {
					set_one(row, column, &colors_[animation_get_color_index(count + cycle_index_)]);
					count++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (get_num_pixels() % 2 != 0) {
					mid_point += 1;
					set_one(mid_point, column, &colors_[cycle_index_]);
				}

				mid_point += 1;

				// Go from the center to the last
				count = 0;
				for (short row = mid_point; row < dimensions_->y; row++) {
					set_one(row, column, &colors_[animation_get_color_index(count + cycle_index_)]);
					count++;
				}
			}
		}
		else {	// Horizontal
			for (unsigned short row = 0; row < dimensions_->y; row++) {
				mid_point = (dimensions_->x / 2) - 1;
				count = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (signed int column = mid_point; column >= 0; column--) {
					set_one(row, column, &colors_[animation_get_color_index(count + cycle_index_)]);
					count++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (get_num_pixels() % 2 != 0) {
					mid_point += 1;
					set_one(row, mid_point, &colors_[cycle_index_]);
				}

				mid_point += 1;

				// Go from the center to the last
				count = 0;
				for (short column = mid_point; column < dimensions_->x; column++) {
					set_one(row, column, &colors_[animation_get_color_index(count + cycle_index_)]);
					count++;
				}
			}
		}

		animation_update_cycle(0, num_colors_);
	}

	/**
		Cycles colors back and forth in a ping-pong pattern.

		Supports vertical orientation.
	*/
	void Section::animation_pong() {
		for (unsigned short row = 0; row < dimensions_->y; row++) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				if (animation_orientation_ == VERTICAL) {
					set_one(row, column, &colors_[animation_get_color_index(row + cycle_index_)]);
				}
				else {	// Horizontal
					set_one(row, column, &colors_[animation_get_color_index(column + cycle_index_)]);
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

		animation_update_cycle(0, num_colors_);
	}

	/// Sets each Pixel to a random stored color.
	void Section::animation_random() {
		for (unsigned int pixel = 0; pixel < get_num_pixels(); pixel++) {
			set_one(pixel, &colors_[Utility::rand() % num_colors_]);
		}
	}

	/// Sets each Pixel to its corresponding color.
	void Section::animation_solid() {
		for (unsigned short row = 0; row < dimensions_->y; row++) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				set_one(row, column, &colors_[animation_get_color_index(column)]);
			}
		}
	}

	/**
	 * Creates a shimmering effect by activating random Pixels.
	 * Set animation_opts_.sparkle_threshold to change the ratio of active Pixels.
	 */
	void Section::animation_sparkle() {
		for (short row = 0; row < dimensions_->y; row++) {
			for (short column = 0; column < dimensions_->x; column++) {
				if ((Utility::rand() % 100) > animation_opts_.sparkle_threshold) {
					set_one(row, column, &colors_[animation_get_color_index(column)]);
				}
				else {
					set_one(row, column, &Colors::BLACK);
				}
			}
		}
	}

	/**
		Incremnets the current animation cycle.
		If reverse_animation_ is true, this decrements the cycle, moving the animation backwards.
		If the animation reaches the end of its cycle, it will jump back (or forward) to the start (or end).

		@param min The minimum possible value of cycle_index_.
		@param max The maximum possible value of cycle_index_.
	*/
	void Section::animation_update_cycle(unsigned short min, unsigned short max) {
		last_cycle_ = last_refresh_;
		if (reverse_animation_) {
			if (cycle_index_ == 0) {
				cycle_index_ = max - 1;
			}
			else {
				cycle_index_--;
			}
		}
		else {
			if (cycle_index_ >= max - 1) {
				cycle_index_ = min;
			}
			else {
				cycle_index_++;
			}
		}
	}

	/**
		Creates a wave effect by scrolling each Color across the Section.

		Supports vertical orientation.
	*/
	void Section::animation_wave() {
		for (unsigned short row = 0; row < dimensions_->y; row++) {
			for (unsigned short column = 0; column < dimensions_->x; column++) {
				if (animation_orientation_ == VERTICAL) {
					set_one(row, column, &colors_[animation_get_color_index(row + cycle_index_)]);
				}
				else {	// Horizontal
					set_one(row, column, &colors_[animation_get_color_index(column + cycle_index_)]);
				}
			}
		}


		animation_update_cycle(0, num_colors_);
	}
}
