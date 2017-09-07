#include "coloranimation.h"

namespace PixelMaestro {
	ColorAnimation::ColorAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) {
		this->section_ = section;
		this->colors_ = colors;
		this->num_colors_ = num_colors;
	}

	/**
	 * Returns whether the animation is fading.
	 * @return True if fading.
	 */
	bool ColorAnimation::get_fade() {
		return fade_;
	}

	/**
	 * Returns the number of Colors in the animation's palette.
	 *
	 * @return Number of Colors in the Color palette.
	 */
	unsigned short ColorAnimation::get_num_colors() {
		return num_colors_;
	}

	/**
	 * Returns whether the animation is running in reverse.
	 * @return True if running in reverse.
	 */
	bool ColorAnimation::get_reverse() {
		return reverse_;
	}

	/**
		Replaces the current color array.

		@param colors New color array.
		@param num_colors Size of the array.
	*/
	void ColorAnimation::set_colors(Colors::RGB* colors, unsigned short num_colors) {
		colors_ = colors;
		num_colors_ = num_colors;
	}

	/**
	 * Toggles fading the animation.
	 * @param fade If true, fade between cycles.
	 */
	void ColorAnimation::set_fade(bool fade) {
		fade_ = fade;
	}

	/**
		Sets whether to run the animation in reverse.

		@param reverse If true, run in reverse.
	 */
	void ColorAnimation::set_reverse(bool reverse) {
		reverse_ = reverse;
	}

	// Private methods

	/**
		Calculates the index of a color.
		Used mainly to determine which color a Pixel should use during an animation based on where it is in the array.
		For example, if the Section has 10 Pixels and 5 Colors, the Pixel at index 7 (count) will use the Color at index 2 (7 % 5 == 2).

		@param count Number to resolve to an index.
		@return Resulting index.
	*/
	unsigned short ColorAnimation::get_color_index(unsigned short count) {
		if (num_colors_ > 0 && count >= num_colors_) {
			count %= num_colors_;
		}

		return count;
	}

	/**
		Incremnets the current animation cycle.
		If reverse_animation_ is true, this decrements the cycle, moving the animation backwards.
		If the animation reaches the end of its cycle, it will jump back (or forward) to the start (or end).

		@param min The minimum possible value of cycle_index_.
		@param max The maximum possible value of cycle_index_.
	*/
	void ColorAnimation::update_cycle(unsigned short min, unsigned short max) {
		if (reverse_) {
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

}
