#include "animation.h"

namespace PixelMaestro {
	/**
	 * Constructor.
	 * @param section The Section that this animation will render in.
	 * @param colors Initial color palette.
	 * @param num_colors The number of colors in the palette.
	 */
	Animation::Animation(Section *section, Colors::RGB* colors, unsigned short num_colors) {
		this->section_ = section;
		this->colors_ = colors;
		this->num_colors_ = num_colors;
	}

	/**
	 * Returns the current cycle index.
	 *
	 * @return Cycle index.
	 */
	unsigned short Animation::get_cycle_index() {
		return cycle_index_;
	}

	/**
	 * Returns whether the animation is fading.
	 * @return True if fading.
	 */
	bool Animation::get_fade() {
		return fade_;
	}

	/**
	 * Returns the number of colors in the animation's palette.
	 *
	 * @return Number of colors in the color palette.
	 */
	unsigned short Animation::get_num_colors() {
		return num_colors_;
	}

	/**
	 * Returns whether the animation is running in reverse.
	 *
	 * @return True if running in reverse.
	 */
	bool Animation::get_reverse() {
		return reverse_;
	}

	/**
		Replaces the current color palette.

		@param colors New color palette.
		@param num_colors Number of colors in the palette.
	*/
	void Animation::set_colors(Colors::RGB* colors, unsigned short num_colors) {
		colors_ = colors;
		num_colors_ = num_colors;
	}

	/**
	 * Sets the cycle index to the specified index.
	 * To be safe, we keep it under num_colors_.
	 *
	 * @param index New cycle index.
	 */
	void Animation::set_cycle_index(unsigned short index) {
		if (index > num_colors_) {
			index %= num_colors_;
		}

		cycle_index_ = index;
	}

	/**
	 * Toggles fading the animation.
	 *
	 * @param fade If true, fade between cycles.
	 */
	void Animation::set_fade(bool fade) {
		fade_ = fade;
	}

	/**
		Sets whether to run the animation in reverse.

		@param reverse If true, run in reverse.
	 */
	void Animation::set_reverse(bool reverse) {
		reverse_ = reverse;
	}

	// Private methods

	/**
		Returns the color at the specified index.
		If the index exceeds the size of the color palette, the index will wrap around to the start of the array and count the remainder.
		For example, if the Section has 10 Pixels and 5 Colors, the Pixel at index 7 will use the color at index 2 (7 % 5 == 2).
		Used mainly to determine which color a Pixel should use during an animation based on where it is in the array.

		@param index Desired index.
		@return Color at the specified index.
	*/
	Colors::RGB* Animation::get_color_at_index(unsigned short index) {
		if (index >= num_colors_) {
			index %= num_colors_;
		}

		return &colors_[index];
	}

	/**
		Incremnets the current animation cycle.
		If reverse_animation_ is true, this decrements the cycle, moving the animation backwards.
		If the animation reaches the end of its cycle, it will jump back (or forward) to the start (or end).

		@param min The minimum possible value of cycle_index_.
		@param max The maximum possible value of cycle_index_.
	*/
	void Animation::update_cycle(unsigned short min, unsigned short max) {
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
