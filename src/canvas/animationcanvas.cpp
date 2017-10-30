/*
 * AnimationCanvas - Displays a Canvas using the Section's underlying Animation.
 */

#include "animationcanvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. This initializes the Canvas with a single frame.
	 * AnimationCanvases "paint" by showing the Section's underlying Animation.
	 * @param section The Canvas' parent Section.
	 */
	AnimationCanvas::AnimationCanvas(Section* section) : Canvas(section) {
		initialize();
	}

	/**
	 * Constructor. Initializes the Canvas with the specified number of frames.
	 * @param section Parent Section.
	 * @param num_frames Number of frames.
	 */
	AnimationCanvas::AnimationCanvas(Section *section, uint16_t num_frames) : Canvas(section, num_frames) {
		initialize();
	}

	/**
	 * Enables the pixel at the specified index.
	 * @param pixel Pixel to activate.
	 */
	void AnimationCanvas::activate(uint32_t pixel) {
		frames_[current_frame_index_][pixel] = 1;
	}

	/**
	 * Deactivates (turns off) the pixel at the specified index.
	 * @param pixel Pixel to deactivate.
	 */
	void AnimationCanvas::deactivate(uint32_t pixel) {
		frames_[current_frame_index_][pixel] = 0;
	}

	/**
	 * Deletes the current frame set.
	 */
	void AnimationCanvas::delete_frames() {
		for (uint16_t i = 0; i < num_frames_; i++) {
			delete[] frames_[i];
		}
		delete[] frames_;
	}

	/**
	 * Returns the color of the Pixel at the specified index.
	 * If the Pixel is activated, return the color of the underlying Animation.
	 * If the Pixel is deactivated, return black.
	 * @param pixel Index of the pixel to check.
	 * @return Pixel's color.
	 */
	Colors::RGB AnimationCanvas::get_pixel_color(uint16_t x, uint16_t y) {
		uint32_t pixel_index;

		if (scroll_ != nullptr && scroll_->repeat) {
			pixel_index = section_->get_pixel_index(
				(x + offset_x_) % section_->get_dimensions()->x,
				(y + offset_y_) % section_->get_dimensions()->y);
		}
		else {
			pixel_index = section_->get_pixel_index(x - offset_x_, y - offset_y_);
		}

		if (in_bounds(pixel_index) && frames_[current_frame_index_][pixel_index] == 1) {
			return *section_->get_pixel(pixel_index)->get_color();
		}
		else {
			return {0, 0, 0};
		}
	}

	CanvasType::Type AnimationCanvas::get_type() {
		return CanvasType::Type::AnimationCanvas;
	}

	/// Builds the Canvas and sets all Pixels off.
	void AnimationCanvas::initialize() {
		frames_ = new bool*[num_frames_];
		for (uint16_t i = 0; i < num_frames_; i++) {
			frames_[i] = new bool[section_->get_dimensions()->size()];
			for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
				frames_[i][pixel] = 0;
			}
		}
	}

	AnimationCanvas::~AnimationCanvas() {
		delete_frames();
	}
}
