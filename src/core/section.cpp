/*
	Section.cpp - Class for controlling multiple Pixels.
	Requires Pixel and Colors classes.
*/

#include "../animation/blinkanimation.h"
#include "../animation/cycleanimation.h"
#include "../animation/fireanimation.h"
#include "../animation/lightninganimation.h"
#include "../animation/mandelbrotanimation.h"
#include "../animation/plasmaanimation.h"
#include "../animation/radialanimation.h"
#include "../animation/randomanimation.h"
#include "../animation/solidanimation.h"
#include "../animation/sparkleanimation.h"
#include "../animation/waveanimation.h"
#include "../canvas/canvas.h"
#include "../utility.h"
#include "colors.h"
#include "pixel.h"
#include "section.h"

namespace PixelMaestro {

	/**
	 * Constructor. Initializes an empty Section.
	 * @param Maestro The Section's parent Maestro.
	 */
	Section::Section() : Section(0, 0) { }

	/**
	 * Constructor. Initializes the Pixel array.
	 * @param x Number of rows in the Section.
	 * @param y Number of columns in the Section.
	 * @param parent Parent Section (if this is an Layer).
	 */
	Section::Section(uint16_t x, uint16_t y, Section* parent) {
		set_dimensions(x, y);
		parent_section_ = parent;
	}

	/**
		Returns the current animation.

		@return Current animation.
	*/
	Animation* Section::get_animation() const {
		return animation_;
	}

	/**
	 * Returns the Section's brightness level.
	 * @return Brightness level.
	 */
	uint8_t Section::get_brightness() const {
		return brightness_;
	}

	/**
	 * Returns the Section's Canvas.
	 * @return Section's Canvas.
	 */
	Canvas* Section::get_canvas() const {
		return canvas_;
	}

	/**
		Returns the size of the Pixel grid.

		@return Size of the Pixel grid.
	*/
	Point* Section::get_dimensions() const {
		return const_cast<Point*>(&dimensions_);
	}

	/**
	 * Returns the Section's parent Maestro.
	 * @return Parent Maestro.
	 */
	Maestro* Section::get_maestro() const {
		return maestro_;
	}

	/**
	 * Returns the Layer (if one exists).
	 *
	 * @return Active Layer.
	 */
	Section::Layer* Section::get_layer() const {
		return layer_;
	}

	/**
	 * Returns whether mirroring is enabled across each axis.
	 * @return Mirror configuration.
	 */
	Section::Mirror* Section::get_mirror() const {
		return mirror_;
	}

	/**
	 * Returns the Section's offset.
	 * @return Offset.
	 */
	Point* Section::get_offset() {
		return &offset_;
	}

	/**
	 * Returns this Section's parent (if this is an Layer).
	 * @return Parent Section.
	 */
	Section* Section::get_parent_section() const {
		return parent_section_;
	}

	/**
	 * Returns the Pixel at the specified index.
	 *
	 * @param x Pixel x coordinate.
	 * @param y Pixel y coordinate.
	 * @return Pixel.
	 */
	Pixel* Section::get_pixel(uint16_t x, uint16_t y) const {
		return &pixels_[dimensions_.get_inline_index(x, y)];
	}

	/**
		Returns the final color of the specified Pixel.

		@param x Pixel x-coordinate.
		@param y Pixel y-coordinate.
		@param base_color The color to use as a base when blending in Layers.
		@return RGB value of the Pixel's final color.
	*/
	Colors::RGB Section::get_pixel_color(uint16_t x, uint16_t y, Colors::RGB* base_color) {
		Colors::RGB final_color;

		// Adjust coordinates based on offset
		uint16_t offset_x = (x + offset_.x) % dimensions_.x;
		uint16_t offset_y = (y + offset_.y) % dimensions_.y;

		// If mirroring is enabled, mirror across the axes.
		if (mirror_ != nullptr) {
			if (mirror_->x) {
				if (offset_y > mirror_->mid_y) {
					offset_y = mirror_->mid_y - (offset_y - mirror_->mid_y);
				}
			}

			if (mirror_->y) {
				if (offset_x > mirror_->mid_x) {
					offset_x = mirror_->mid_x - (offset_x - mirror_->mid_x);
				}
			}
		}

		// Get the Pixel's color
		final_color = pixels_[dimensions_.get_inline_index(offset_x, offset_y)].get_color();

		/*
		 * If this Section *is* a Layer, combine this Pixel's color with its parent Pixel's color.
		 * This is done recursively, with each Layer building on top of its parent Section.
		 */
		if (parent_section_ != nullptr) {
			final_color = Colors::mix_colors(
							 base_color,
							 &final_color,
							 parent_section_->get_layer()->mix_mode,
							 parent_section_->get_layer()->alpha);
		}

		// If this Section *has* a Layer, merge in the Layer's color output.
		if (layer_ != nullptr) {
			final_color = layer_->section->get_pixel_color(x, y, &final_color);
		}

		// Return color with brightness calculated
		return final_color * static_cast<float>(brightness_ / static_cast<float>(255));
	}

	/**
	 * Returns the Section's scrolling behavior.
	 * @return Scrolling behavior.
	 */
	Section::Scroll* Section::get_scroll() const {
		return scroll_;
	}

	/**
	 * Deletes the current Animation.
	 *
	 * @param clear_pixels If true, Pixels are cleared.
	 */
	void Section::remove_animation(bool clear_pixels) {
		delete animation_;
		animation_ = nullptr;

		// Reset Pixel colors
		if (clear_pixels) {
			for (uint32_t pixel = 0; pixel < dimensions_.size(); pixel++) {
				pixels_[pixel].clear();
			}
		}
	}

	/**
	 * Deletes the current Canvas.
	 */
	void Section::remove_canvas() {
		delete canvas_;
		canvas_ = nullptr;
	}

	/**
	 * Deletes the current Layer.
	 */
	void Section::remove_layer() {
		delete layer_;
		layer_ = nullptr;
	}

	/**
	 * Deletes the Section's scrolling behavior.
	 */
	void Section::remove_scroll() {
		delete scroll_;
		scroll_ = nullptr;
	}

	/**
	 * Sets a new Animation.
	 *
	 * @param type Animation type.
	 * @param palette The color palette to use.
	 * @param preserve_settings If true, the generic configurations in the old Animation (Palette, cycle index, orientation, fade, reverse, speed, and pause) are copied to the new Animation.
	 * @return New Animation.
	 */
	Animation* Section::set_animation(AnimationType animation_type, bool preserve_settings) {
		Animation* new_animation = nullptr;
		switch(animation_type) {
			case AnimationType::Blink:
				new_animation = new BlinkAnimation(*this);
				break;
			case AnimationType::Cycle:
				new_animation = new CycleAnimation(*this);
				break;
			case AnimationType::Fire:
				new_animation = new FireAnimation(*this);
				break;
			case AnimationType::Lightning:
				new_animation = new LightningAnimation(*this);
				break;
			case AnimationType::Mandelbrot:
				new_animation = new MandelbrotAnimation(*this);
				break;
			case AnimationType::Plasma:
				new_animation = new PlasmaAnimation(*this);
				break;
			case AnimationType::Radial:
				new_animation = new RadialAnimation(*this);
				break;
			case AnimationType::Random:
				new_animation = new RandomAnimation(*this);
				break;
			case AnimationType::Solid:
				new_animation = new SolidAnimation(*this);
				break;
			case AnimationType::Sparkle:
				new_animation = new SparkleAnimation(*this);
				break;
			case AnimationType::Wave:
				new_animation = new WaveAnimation(*this);
				break;
		}

		/*
		 * Check for an existing Animation.
		 * If one exists and preserve_settings is true, copy the old Animation's settings to the new Animation.
		 */
		if (this->animation_ != nullptr) {
			if (preserve_settings) {
				new_animation->set_palette(this->animation_->get_palette());
				new_animation->set_cycle_index(this->animation_->get_cycle_index());
				new_animation->set_fade(this->animation_->get_fade());
				new_animation->set_orientation(this->animation_->get_orientation());
				new_animation->set_reverse(this->animation_->get_reverse());

				if (this->animation_->get_timer() != nullptr) {
					new_animation->set_timer(this->animation_->get_timer()->get_interval(), this->animation_->get_timer()->get_delay());
				}
			}
			remove_animation(false);
		}

		this->animation_ = new_animation;
		return animation_;
	}

	/**
	 * Sets the overall brightness of the Section.
	 * 255 is full brightness, and 0 is completely dark.
	 * @param brightness Brightness level (0 - 255).
	 */
	void Section::set_brightness(uint8_t brightness) {
		this->brightness_ = brightness;
	}

	/**
	 * Sets a new Canvas of the specified type.
	 * This will overwrite the existing Canvas.
	 * @param num_frames The number of frames in the Canvas.
	 * @return The new Canvas.
	 */
	Canvas* Section::set_canvas(uint16_t num_frames) {
		remove_canvas();
		canvas_ = new Canvas(*this, num_frames);
		return canvas_;
	}

	/**
	 * Sets the size of the Section.
	 * @param x Number of Pixels along the x-coordinate.
	 * @param y Number of Pixels along the y-coordinate.
	 */
	void Section::set_dimensions(uint16_t x, uint16_t y) {
		dimensions_.x = x;
		dimensions_.y = y;

		// Resize the Pixel grid
		delete [] pixels_;
		pixels_ = new Pixel[dimensions_.size()];

		// Resize the Animation
		if (animation_ != nullptr) {
			animation_->rebuild_map();
		}

		// Resize the Canvas
		if (canvas_ != nullptr) {
			canvas_->initialize();
		}

		// Resize the Layer
		if (layer_ != nullptr) {
			layer_->section->set_dimensions(dimensions_.x, dimensions_.y);
		}

		// If mirroring is enabled, recalculate the midway points
		if (mirror_ != nullptr) {
			mirror_->set(mirror_->x, mirror_->y, this->dimensions_);
		}
	}

	/**
	 * Sets a new Layer.
	 * If an Layer already exists, this updates the existing Layer.
	 * @param mix_mode The method for blending the Layer.
	 * @param alpha The Layer's transparency (0 - 255.
	 * @return New Layer.
	 */
	Section::Layer* Section::set_layer(Colors::MixMode mix_mode, uint8_t alpha) {
		if (layer_ == nullptr) {
			layer_ = new Layer(this, mix_mode, alpha);
		}
		else {
			layer_->mix_mode = mix_mode;
			layer_->alpha = alpha;
		}

		return layer_;
	}

	/**
	 * Sets the Section's parent Maestro.
	 * @param maestro Parent Maestro.
	 */
	void Section::set_maestro(Maestro* maestro) {
		this->maestro_ = maestro;
	}

	/**
	 * Mirrors the Section across the axes.
	 * If both x and y are false, mirroring is disabled.
	 * @param x Mirror the x axis.
	 * @param y Mirror the y axis.
	 */
	Section::Mirror& Section::set_mirror(bool x, bool y) {
		if (x == false && y == false) {
			delete mirror_;
			mirror_ = nullptr;
		}
		else {
			if (mirror_ == nullptr) {
				mirror_ = new Mirror();
			}

			mirror_->set(x, y, this->dimensions_);
		}

		return *mirror_;
	}

	/**
	 * Sets the Section's offset, which shifts the Section's output along the Pixel grid.
	 * @param x Offset along the x axis.
	 * @param y Offset along the y axis.
	 * @return Offset.
	 */
	Point& Section::set_offset(uint16_t x, uint16_t y) {
		offset_.set(x, y);
		return offset_;
	}

	/**
		Sets the specified Pixel to a new color.

		@param x The Pixel's column.
		@param y The Pixel's row.
		@param color New color.
		@param step_count Number of intermediate steps until the new color is reached.
	*/
	void Section::set_one(uint16_t x, uint16_t y, const Colors::RGB& color, uint8_t step_count) {
		// Only continue if the Pixel is within the bounds of the array.
		if (dimensions_.in_bounds(x, y)) {
			uint32_t index = dimensions_.get_inline_index(x, y);
			pixels_[index].set_next_color(color, step_count);
		}
	}

	/**
	 * Sets the direction and rate that the Section will scroll.
	 * The values determine the amount of time until the Section completes a single scroll along the respective axis.
	 * Using a negative value reverses the scrolling direction.
	 * Setting either axis to 0 disables scrolling on that axis.
	 *
	 * @param x Scrolling interval along the x axis.
	 * @param y Scrolling interval along the y axis.
	 * @param reverse_x If true, reverses the scrolling direction along the x axis.
	 * @param reverse_y If true, reverses the scrolling direction along the y axis.
	 */
	Section::Scroll& Section::set_scroll(uint16_t x, uint16_t y, bool reverse_x, bool reverse_y) {
		if (scroll_ == nullptr) {
			scroll_ = new Scroll();
		}

		scroll_->set(maestro_->get_timer()->get_interval(), &dimensions_, x, y, reverse_x, reverse_y);

		return *scroll_;
	}

	/**
	 * Sets the last update time of each component's timer.
	 * @param new_time New last refresh time.
	 */
	void Section::sync(const uint32_t &new_time) {
		if (layer_ != nullptr) {
			layer_->section->sync(new_time);
		}
		if (animation_ != nullptr) {
			animation_->get_timer()->set_last_time(new_time);
		}
		if (canvas_ != nullptr && canvas_->get_frame_timer() != nullptr) {
			canvas_->get_frame_timer()->set_last_time(new_time);
		}
		if (scroll_ != nullptr) {
			if (scroll_->timer_x != nullptr) scroll_->timer_x->set_last_time(new_time);
			if (scroll_->timer_y != nullptr) scroll_->timer_y->set_last_time(new_time);
		}
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Section::update(const uint32_t& current_time) {

		/*
		 * First, update the Animation. This sets next_color_ for each Pixel.
		 * Second, update the Canvas, which overwrites each Pixel's next_color_ where necessary.
		 * Now that next_color_ is set, update each Pixel. This generates each Pixel's "true" color.
		 * Finally, run update_scroll() to recalculate the offset to use when rendering Pixels, then update the layer.
		 */
		if (animation_ != nullptr) {
			animation_->update(current_time);
		}

		if (canvas_ != nullptr) {
			canvas_->update(current_time);
		}

		for (uint32_t pixel = 0; pixel < dimensions_.size(); pixel++) {
			pixels_[pixel].update();
		}

		if (scroll_ != nullptr) {
			update_scroll(current_time);
		}

		if (layer_ != nullptr) {
			layer_->section->update(current_time);
		}
	}

	/**
	 * Scrolls the Section.
	 * @param current_time The program's current runtime.
	 */
	void Section::update_scroll(const uint32_t &current_time) {

		// Scroll x axis
		if (scroll_->timer_x != nullptr || scroll_->step_x != 0) {
			uint16_t x_step = 0;
			// If a timer is used (scrolling < 1 pixel per update), determine whether it's time to scroll.
			if (scroll_->timer_x != nullptr) {
				if (scroll_->timer_x->update(current_time)) {
					x_step = 1;
				}
			}
			// If a timer is not used (scrolling > 1 pixel per update), apply the scroll amount directly to the offset.
			else if (scroll_->step_x > 0) {
				x_step = scroll_->step_x;
			}

			// Check to see if we need to reset the offset
			if (!scroll_->reverse_x && offset_.x >= dimensions_.x) {
				offset_.x = 0;
			}
			else if (scroll_->reverse_x && offset_.x == 0) {
				offset_.x = dimensions_.x;
			}

			// Finally, apply the movement
			if (!scroll_->reverse_x) {
				offset_.x += x_step;
			}
			else {
				offset_.x -= x_step;
			}
		}


		// Repeat for y axis
		if (scroll_->timer_y != nullptr || scroll_->step_y != 0) {
			uint16_t y_step = 0;
			if (scroll_->timer_y != nullptr) {
				if (scroll_->timer_y->update(current_time)) {
					y_step = 1;
				}
			}
			else if (scroll_->step_y > 0) {
				y_step = scroll_->step_y;
			}

			// Check to see if we need to reset the offset
			if (!scroll_->reverse_y && offset_.y >= dimensions_.y) {
				offset_.y = 0;
			}
			else if (scroll_->reverse_y && offset_.y == 0) {
				offset_.y = dimensions_.y;
			}

			// Finally, apply the movement
			if (!scroll_->reverse_y) {
				offset_.y += y_step;
			}
			else {
				offset_.y -= y_step;
			}
		}
	}

	Section::~Section() {
		remove_animation(false);
		remove_canvas();
		remove_layer();
		remove_scroll();

		delete mirror_;
		delete [] pixels_;
	}
}
