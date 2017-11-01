/*
	Section.cpp - Class for controlling multiple Pixels.
	Requires Pixel and Colors classes.
*/

#include "../animation/blinkanimation.h"
#include "../animation/cycleanimation.h"
#include "../animation/lightninganimation.h"
#include "../animation/mandelbrotanimation.h"
#include "../animation/mergeanimation.h"
#include "../animation/plasmaanimation.h"
#include "../animation/radialanimation.h"
#include "../animation/randomanimation.h"
#include "../animation/solidanimation.h"
#include "../animation/sparkleanimation.h"
#include "../animation/waveanimation.h"
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
		set_dimensions(dimensions.x, dimensions.y);
	}

	/**
	 * Constructor. Initializes the Pixel array.
	 * @param x Number of rows in the Section.
	 * @param y Number of columns in the Section.
	 */
	Section::Section(uint16_t x, uint16_t y) {
		set_dimensions(x, y);
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
		Returns the final color of the specified Pixel.

		@param x Pixel x-coordinate.
		@param y Pixel y-coordinate.
		@return RGB value of the Pixel's final color.
	*/
	Colors::RGB Section::get_pixel_color(uint16_t x, uint16_t y) {
		Colors::RGB color;

		// If there's a Canvas, get the color supplied by the Canvas.
		if (canvas_ != nullptr) {
			color = canvas_->get_pixel_color(x, y);
		}
		else {
			color = *pixels_[dimensions_.get_inline_index(x, y)].get_color();
		}

		// If there's an Overlay, return the Overlay color mixed with the Section (or Canvas) color.
		if (overlay_ != nullptr) {
			return Colors::mix_colors(color, overlay_->section->get_pixel_color(x, y), overlay_->mix_mode, overlay_->alpha);
		}

		return color;
	}

	/**
		Returns the Section's refresh rate.

		@return The refresh rate of the Section.
	*/
	uint16_t Section::get_refresh_interval() {
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
	void Section::set_all(Colors::RGB color) {
		for (uint32_t pixel = 0; pixel < dimensions_.size(); pixel++) {
			set_one(pixel, color);
		}
	}

	/**
	 * Sets a new Animation.
	 * This will delete and overwrite an existing Animation.
	 * @param type Animation type.
	 * @param colors The color palette.
	 * @param num_colors The number of colors in the palette.
	 * @param preserve_cycle_index If true, the cycle index from the old Animation transfers over to the new Animation.
	 * @return New Animation.
	 */
	Animation* Section::set_animation(AnimationType::Type animation_type, Colors::RGB *colors, uint8_t num_colors, bool preserve_cycle_index) {
		Animation* animation = nullptr;
		switch(animation_type) {
			case AnimationType::Type::Blink:
				animation = new BlinkAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Cycle:
				animation = new CycleAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Lightning:
				animation = new LightningAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Mandelbrot:
				animation = new MandelbrotAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Merge:
				animation = new MergeAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Plasma:
				animation = new PlasmaAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Radial:
				animation = new RadialAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Random:
				animation = new RandomAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Solid:
				animation = new SolidAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Sparkle:
				animation = new SparkleAnimation(colors, num_colors);
				break;
			case AnimationType::Type::Wave:
				animation = new WaveAnimation(colors, num_colors);
				break;
		}

		if (animation_) {
			if (preserve_cycle_index) {
				animation->set_cycle_index(animation_->get_cycle_index());
			}
			remove_animation();
		}

		animation_ = animation;
		return animation_;
	}

	/**
	 * Sets a new Canvas of the specified type.
	 * This will delete and overwrite an existing Canvas.
	 * @param type The type of Canvas to create.
	 * @param num_frames The number of frames in the Canvas.
	 * @return The new Canvas.
	 */
	Canvas* Section::set_canvas(CanvasType::Type type, uint16_t num_frames) {
		remove_canvas();

		switch (type) {
			case CanvasType::Type::AnimationCanvas:
				canvas_ = new AnimationCanvas(this, num_frames);
				break;
			case CanvasType::Type::ColorCanvas:
				canvas_ = new ColorCanvas(this, num_frames);
				break;
		}

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

		// Reinitialize the Canvas
		if (canvas_ != nullptr) {
			canvas_->initialize();
		}

		// Reinitialize the Overlay
		if (overlay_ != nullptr) {
			overlay_->section->set_dimensions(dimensions_.x, dimensions_.y);
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param pixel The index of the Pixel to update.
		@param color New color.
	*/
	void Section::set_one(uint32_t pixel, Colors::RGB color) {
		// Only continue if Pixel is within the bounds of the array.
		if (pixel < dimensions_.size()) {
			/*
				If pause is enabled, trick the Pixel into thinking the cycle is shorter than it is.
				This results in the Pixel finishing early and waiting until the next cycle.
			*/
			// TODO: Can we get the animation to calculate speed, pause, and refresh rate so we don't have to do the calculation per-Pixel?
			pixels_[pixel].set_next_color(color, animation_->get_fade(), animation_->get_speed() - animation_->get_pause(), *refresh_interval_);
		}
	}

	/**
		Sets the specified Pixel to a new color.

		@param x The column number of the Pixel.
		@param y The row number of the Pixel.
		@param color New color.
	*/
	void Section::set_one(uint16_t x, uint16_t y, Colors::RGB color) {
		set_one(dimensions_.get_inline_index(x, y), color);
	}

	/**
	 * Sets a new Overlay.
	 * This will delete and overwrite an existing Overlay.
	 * @param mix_mode The method for blending the Overlay.
	 * @param alpha The Overlay's transparency (0 - 255.
	 * @return New Overlay.
	 */
	Section::Overlay* Section::set_overlay(Colors::MixMode mix_mode, uint8_t alpha) {
		remove_overlay();
		overlay_ = new Overlay(dimensions_, mix_mode, alpha);
		overlay_->section->set_refresh_interval(refresh_interval_);
		return overlay_;
	}

	/**
		Sets the refresh rate of the Section (how quickly the Pixels update).

		@param interval Rate in milliseconds between Pixel redraws.
	*/
	void Section::set_refresh_interval(uint16_t* interval) {
		refresh_interval_ = interval;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Section::update(const uint32_t& current_time) {

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
			for (uint32_t pixel = 0; pixel < dimensions_.size(); pixel++) {
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
