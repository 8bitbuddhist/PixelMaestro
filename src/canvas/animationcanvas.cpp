/*
 * AnimationCanvas - Displays a Canvas using the Section's underlying Animation.
 */

#include "animationcanvas.h"
#include "../utility.h"

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
	 * Enables the pixel at the specified coordinates.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 */
	void AnimationCanvas::activate(uint16_t x, uint16_t y) {
		frames_[current_frame_index_][get_section()->get_dimensions()->get_inline_index(x, y)] = 1;
	}

	/**
	 * Deactivates (turns off) the pixel at the specified index.
	 * @param pixel Pixel to deactivate.
	 */
	void AnimationCanvas::deactivate(uint16_t x, uint16_t y) {
		frames_[current_frame_index_][get_section()->get_dimensions()->get_inline_index(x, y)] = 0;
	}

	/**
	 * Deletes the current frame set.
	 */
	void AnimationCanvas::delete_frames() {
		if (frames_ != nullptr) {
			for (uint16_t i = 0; i < num_frames_; i++) {
				delete[] frames_[i];
			}
		}
		delete[] frames_;
	}

	/**
	 * Draws an existing frame over the current frame.
	 * @param frame Frame to draw.
	 * @param size_x Frame width.
	 * @param size_y Frame height.
	 */
	void AnimationCanvas::draw_frame(bool *frame, uint16_t size_x, uint16_t size_y) {
		clear();
		Point frame_bounds(size_x, size_y);
		for (uint16_t y = 0; y < size_y; y++) {
			for (uint16_t x = 0; x < size_x; x++) {
				if (in_bounds(x, y) && frame[frame_bounds.get_inline_index(x, y)] == true) {
					draw_point(x, y);
				}
			}
		}
	}

	/**
	 * Returns the frame at the specified index.
	 * @param frame Index of the frame.
	 * @return Frame at index.
	 */
	bool* AnimationCanvas::get_frame(uint16_t frame) const {
		return frames_[frame];
	}

	/**
	 * Returns the color of the Pixel at the specified index.
	 * If the Pixel is activated, return the color of the underlying Animation.
	 * If the Pixel is deactivated, return black.
	 * @param pixel Index of the pixel to check.
	 * @return Pixel's color.
	 */
	Colors::RGB AnimationCanvas::get_pixel_color(uint16_t x, uint16_t y) {
		if (in_bounds(x, y) && frames_[current_frame_index_][section_->get_dimensions()->get_inline_index(x, y)] == 1) {
			return *section_->get_pixel(x, y)->get_color();
		}
		else {
			return {0, 0, 0};
		}
	}

	/**
	 * Returns the Canvas type.
	 * @return Type of Canvas.
	 */
	CanvasType AnimationCanvas::get_type() const {
		return CanvasType::AnimationCanvas;
	}

	/// Builds the Canvas and defaults all Pixels to off.
	void AnimationCanvas::initialize() {
		delete_frames();
		frames_ = new bool*[num_frames_];
		for (uint16_t i = 0; i < num_frames_; i++) {
			frames_[i] = new bool[section_->get_dimensions()->size()] {0};
		}
	}

	AnimationCanvas::~AnimationCanvas() {
		delete_frames();
	}
}
