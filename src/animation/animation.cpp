/*
 * Animation - Base class for rendering Animations on a Section.
 */

#include "animation.h"

namespace PixelMaestro {
	/**
	 * Constructor. Initializes the timer and map.
	 * @param section The Section that this animation will render in.
	 */
	Animation::Animation(Section& section) : section_(section) {
		this->timer_ = new AnimationTimer(*this);
		rebuild_map();
		initialized_ = true;
	}

	/**
	 * Returns the Animation's center.
	 * @return Animation's center.
	 */
	Point& Animation::get_center() const {
		return const_cast<Point&>(center_);
	}

	/**
	 * Returns the current frame index.
	 *
	 * @return Current frame index.
	 */
	uint8_t Animation::get_frame_index() const {
		return frame_index_;
	}

	/**
	 * Returns whether the animation is fading.
	 * @return True if fading.
	 */
	bool Animation::get_fade() const {
		return fade_;
	}

	/**
	 * Returns the animation's orientation.
	 * @return Animation's orientation
	 */
	Animation::Orientation Animation::get_orientation() const {
		return orientation_;
	}

	/**
	 * Returns the color palette.
	 * @return Color palette.
	 */
	Palette* Animation::get_palette() const {
		return palette_;
	}

	/**
	 * Returns whether the animation is running in reverse.
	 *
	 * @return True if running in reverse.
	 */
	bool Animation::get_reverse() const {
		return reverse_;
	}

	/**
	 * Returns the Animation's parent Section.
	 * @return Parent Section.
	 */
	Section& Animation::get_section() const {
		return section_;
	}

	/**
	 * Returns the animation's timer.
	 * @return Animation timer.
	 */
	AnimationTimer* Animation::get_timer() const {
		return timer_;
	}

	/**
	 * Returns the type of Animation.
	 * @return Animation type.
	 */
	AnimationType Animation::get_type() const {
		return type_;
	}

	/**
	 * Regenerates the color-to-pixel map.
	 */
	void Animation::rebuild_map() {
		// Regenerate the color-to-pixel mapping.
		for (uint16_t y = 0; y < dimensions_.y; y++) {
			delete [] map_[y];
		}
		delete [] map_;

		dimensions_ = section_.get_dimensions();

		map_ = new uint8_t*[dimensions_.y];
		for (uint16_t y = 0; y < dimensions_.y; y++) {
			map_[y]	= new uint8_t[dimensions_.x] {0};
		}

		set_center(dimensions_.x / 2, dimensions_.y / 2);
	}

	/**
	 * Sets the center of the Animation. Only applies to certain Animations.
	 * @param x Center along the x axis.
	 * @param y Center along the y axis.
	 */
	void Animation::set_center(uint16_t x, uint16_t y) {
		center_.set(x, y);
		if (initialized_) map();
	}

	/**
	 * Sets the frame index to the specified index.
	 *
	 * @param index New frame index.
	 */
	void Animation::set_frame_index(uint8_t index) {
		if (palette_ != nullptr && index > palette_->get_num_colors()) {
			index %= palette_->get_num_colors();
		}

		frame_index_ = index;
	}

	/**
	 * Toggles fading the animation.
	 *
	 * @param fade If true, fade between frames.
	 */
	void Animation::set_fade(bool fade) {
		fade_ = fade;
		timer_->recalculate_step_count();
	}

	/**
	 * Assigns the specified Pixel to the specified color.
	 * @param x Pixel's x coordinate.
	 * @param y Pixel's y coordinate.
	 * @param color_index Index of the color to set.
	 */
	void Animation::set_map_color_index(uint16_t x, uint16_t y, uint8_t color_index) {
		if (orientation_ == Orientation::HorizontalFlipped || orientation_ == Orientation::VerticalFlipped) {
			map_[(dimensions_.y - 1) - y][(dimensions_.x - 1) - x] = color_index;
		}
		else {
			map_[y][x] = color_index;
		}
	}

	/**
	 * Sets the animation's orientation.
	 *
	 * @param orientation New orientation.
	 */
	void Animation::set_orientation(Orientation orientation) {
		this->orientation_ = orientation;
		map();
	}

	/**
	 * Sets a new color palette.
	 *
	 * @param palette New Palette.
	 */
	void Animation::set_palette(Palette& palette) {
		this->palette_ = &palette;
	}

	/**
		Sets whether to run the animation in reverse.

		@param reverse If true, run in reverse.
	 */
	void Animation::set_reverse(bool reverse) {
		this->reverse_ = reverse;
	}

	/**
	 * Sets the amount of time between animation updates.
	 *
	 * @param speed Amount of time (in milliseconds) between animation frames.
	 * @param delay Amount of time (in milliseconds) to wait before starting an animation frame.
	 */
	AnimationTimer& Animation::set_timer(uint16_t speed, uint16_t delay) {
		timer_->set_interval(speed, delay);
		timer_->recalculate_step_count();

		return *timer_;
	}

	/**
	 * Updates the animation.
	 * This checks to see if the animation should update, then calls the derived class's update method.
	 * Finally, it renders the mapped color to each Pixel.
	 * @param current_time The current runtime.
	 * @return True if the update was processed.
	 */
	bool Animation::update(const uint32_t &current_time) {
		// If the color palette is not set, exit.
		if (palette_ == nullptr || palette_->get_num_colors() == 0) return false;

		if (timer_->update(current_time)) {
			// Call the derived Animation's update routine
			update();
			section_.set_step_count(timer_->get_step_count());
			for (uint16_t x = 0; x < section_.get_dimensions().x; x++) {
				for (uint16_t y = 0; y < section_.get_dimensions().y; y++) {
					// Color index 255 reserved for black
					if (map_[y][x] == 255) {
						section_.set_pixel_color(x, y, Colors::RGB(0, 0, 0));
					}
					else {
						section_.set_pixel_color(x,
							y,
							palette_->get_color_at_index(map_[y][x] + frame_index_)
						);
					}
				}
			}

			return true;
		}

		return false;
	}

	/**
		Incremnets the current animation frame.
		If reverse_animation_ is true, this decrements the frame, moving the animation backwards.
		If the animation reaches the end of its frame, it will jump back (or forward) to the start (or end).

		@param min The minimum possible value of frame_index_.
		@param max The maximum possible value of frame_index_.
	*/
	void Animation::update_frame(uint8_t min, uint8_t max) {
		if (reverse_) {
			if (frame_index_ == 0) {
				frame_index_ = max - 1;
			}
			else {
				frame_index_--;
			}
		}
		else {
			if (frame_index_ >= max - 1) {
				frame_index_ = min;
			}
			else {
				frame_index_++;
			}
		}
	}

	Animation::~Animation() {
		delete timer_;

		// Destroy the map
		for (uint16_t y = 0; y < dimensions_.y; y++) {
			delete [] map_[y];
		}
		delete [] map_;
	}
}
