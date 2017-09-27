/*
	Section.cpp - Class for controlling multiple Pixels.
	Requires Pixel and Colors classes.
*/

#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "colors.h"
#include "pixel.h"
#include "section.h"

namespace PixelMaestro {

	/**
	 * Constructor. Initializes the Pixel array.
	 * @param dimensions Initial layout (rows and columns) of the Pixels.
	 */
	Section::Section(Point dimensions) {
		set_dimensions(dimensions);
	}

	/**
	 * Constructor. Initializes the Pixel array.
	 * @param x Number of rows in the Section.
	 * @param y Number of columns in the Section.
	 */
	Section::Section(unsigned short x, unsigned short y) {
		set_dimensions(x, y);
	}

	/**
	 * Creates a new Canvas of the specified type.
	 * This will overwrite an existing Canvas.
	 * @param type The type of Canvas to create.
	 * @return The new Canvas.
	 */
	Canvas* Section::add_canvas(CanvasType::Type type) {
		remove_canvas();

		switch (type) {
			case CanvasType::Type::AnimationCanvas:
				canvas_ = new AnimationCanvas(this);
				break;
			case CanvasType::Type::ColorCanvas:
				canvas_ = new ColorCanvas(this);
				break;
		}

		return canvas_;
	}

	/**
	 * Creates a new Overlay.
	 * This will overwrite an existing Overlay.
	 * @param mix_mode The method for blending the Overlay.
	 * @param alpha The Overlay's transparency (0 - 255.
	 * @return New Overlay.
	 */
	Section::Overlay* Section::add_overlay(Colors::MixMode mix_mode, unsigned char alpha) {
		remove_overlay();
		overlay_ = new Overlay(dimensions_, mix_mode, alpha);
		overlay_->section->set_refresh_interval(refresh_interval_);
		return overlay_;
	}

	/**
		Returns the current animation.

		@return Current animation.
	*/
	Animation* Section::get_animation() {
		return animation_;
	}

	/**
	 * Returns the Section's Canvas.
	 * @return Section's Canvas.
	 */
	Canvas* Section::get_canvas() {
		return canvas_;
	}

	/**
		Returns the size of the Pixel grid.

		@return Size of the Pixel grid.
	*/
	Point* Section::get_dimensions() {
		return &dimensions_;
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
		Returns the final color of the specified Pixel.

		@param pixel Index of the Pixel.
		@return RGB value of the Pixel's final color.
	*/
	Colors::RGB Section::get_pixel_color(unsigned int pixel) {
		Colors::RGB color;

		// If there's a Canvas, get the color supplied by the Canvas.
		if (canvas_ != nullptr) {
			color = canvas_->get_pixel_color(pixel);
		}
		else {
			color = *pixels_[pixel].get_color();
		}

		// If there's an Overlay, return the Overlay color mixed with the Section (or Canvas) color.
		if (overlay_ != nullptr) {
			return Colors::mix_colors(color, overlay_->section->get_pixel_color(pixel), overlay_->mix_mode, overlay_->alpha);
		}

		return color;
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
		return (y * dimensions_.x) + x;
	}

	/**
		Returns the Section's refresh rate.

		@return The refresh rate of the Section.
	*/
	unsigned short Section::get_refresh_interval() {
		return *refresh_interval_;
	}

	/**
	 * Deletes the current Animation.
	 */
	void Section::remove_animation() {
		delete animation_;
		animation_ = nullptr;
	}

	/**
	 * Deletes the current Canvas.
	 */
	void Section::remove_canvas() {
		delete canvas_;
		canvas_ = nullptr;
	}

	/**
	 * Deletes the current Overlay.
	 */
	void Section::remove_overlay() {
		delete overlay_;
		overlay_ = nullptr;
	}

	/**
		Sets all Pixels to the specified color.

		@param color New color.
	*/
	void Section::set_all(Colors::RGB* color) {
		for (unsigned int pixel = 0; pixel < dimensions_.size(); pixel++) {
			set_one(pixel, color);
		}
	}

	/**
		Changes the current animation.

		@param animation New animation.
		@param preserve_cycle_index If true, resume from the cycle_index of the previous animation.
		@return The new animation.
	*/
	Animation* Section::set_animation(Animation* animation, bool preserve_cycle_index) {
		if (preserve_cycle_index && animation_) {
			animation->set_cycle_index(animation_->get_cycle_index());
		}

		remove_animation();

		animation_ = animation;
		return animation_;
	}

	/**
		Sets the Pixel array and layout used in the Section.

		@param dimensions Dimensions of the Pixel array.
	*/
	void Section::set_dimensions(Point dimensions) {
		set_dimensions(dimensions.x, dimensions.y);
	}

	/**
	 * Sets the size of the Section.
	 * @param x Number of Pixels along the x-coordinate.
	 * @param y Number of Pixels along the y-coordinate.
	 */
	void Section::set_dimensions(unsigned short x, unsigned short y) {
		dimensions_.x = x;
		dimensions_.y = y;

		// Resize the Pixel grid
		delete [] pixels_;
		pixels_ = new Pixel[dimensions_.size()];

		// Reinitialize the Canvas
		if (canvas_ != nullptr) {
			canvas_->initialize_pattern();
		}

		// Reinitialize the Overlay
		if (overlay_ != nullptr) {
			overlay_->section->set_dimensions(dimensions_);
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param pixel The index of the Pixel to update.
		@param color New color.
	*/
	void Section::set_one(unsigned int pixel, Colors::RGB* color) {
		// Only continue if Pixel is within the bounds of the array.
		if (pixel < dimensions_.size()) {
			/*
				If pause is enabled, trick the Pixel into thinking the cycle is shorter than it is.
				This results in the Pixel finishing early and waiting until the next cycle.
			*/
			pixels_[pixel].set_next_color(color, animation_->get_fade(), animation_->get_speed() - animation_->get_pause(), *refresh_interval_);
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param x The column number of the Pixel.
		@param y The row number of the Pixel.
		@param color New color.
	*/
	void Section::set_one(unsigned short x, unsigned short y, Colors::RGB* color) {
		set_one(get_pixel_index(x, y), color);
	}

	/**
		Sets the refresh rate of the Section (how quickly the Pixels update).

		@param interval Rate in milliseconds between Pixel redraws.
	*/
	void Section::set_refresh_interval(unsigned short* interval) {
		refresh_interval_ = interval;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Section::update(const unsigned long& current_time) {

		// If this Section has an Overlay or Canvas, update them first.
		if (overlay_ != nullptr) {
			overlay_->section->update(current_time);
		}

		if (canvas_ != nullptr) {
			canvas_->update(current_time);
		}

		/*
		 * Update the Pixel grid.
		 * Only update if an Animation is set and either:
		 *		a) The Animation has changed
		 *		b) Fading is enabled
		 */
		if (animation_ != nullptr &&
				(animation_->update(current_time, this) ||
				 animation_->get_fade())) {
			for (unsigned int pixel = 0; pixel < dimensions_.size(); pixel++) {
				pixels_[pixel].update();
			}
		}
	}

	Section::~Section() {
		remove_animation();
		remove_canvas();
		remove_overlay();

		delete [] pixels_;
	}
}
