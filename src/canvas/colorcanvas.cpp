/*
 * ColorCanvas - Displays patterns using a grid of colors.
 */

#include "colorcanvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. Initializes the Canvas with a single frame.
	 * @param section Parent Section.
	 */
	ColorCanvas::ColorCanvas(Section* section) : Canvas(section) {
		initialize();
	}

	/**
	 * Constructor. Initializes the Canvas with the specified number of frames.
	 * @param section Parent Section.
	 * @param num_frames Number of frames.
	 */
	ColorCanvas::ColorCanvas(Section *section, uint16_t num_frames) : Canvas(section, num_frames) {
		initialize();
	}

	/**
	 * Deletes the current frame set.
	 */
	void ColorCanvas::delete_frames() {
		for (uint16_t i = 0; i < num_frames_; i++) {
			delete[] frames_[i];
		}
		delete[] frames_;
	}

	/**
	 * Draws an existing frame over the current frame.
	 * @param frame Frame to draw.
	 * @param size_x Frame width.
	 * @param size_y Frame height.
	 */
	void ColorCanvas::draw_frame(Colors::RGB *frame, uint16_t size_x, uint16_t size_y) {
		clear();
		Point frame_bounds = Point(size_x, size_y);
		for (uint16_t y = 0; y < size_y; y++) {
			for (uint16_t x = 0; x < size_x; x++) {
				if (in_bounds(x, y)) {
					draw_point(frame[frame_bounds.get_inline_index(x, y)], x, y);
				}
			}
		}
	}

	/**
	 * Returns the frame at the specified index.
	 * @param frame Index of the frame.
	 * @return Frame at index.
	 */
	Colors::RGB* ColorCanvas::get_frame(uint16_t frame) const {
		return frames_[frame];
	}

	/**
	 * Returns the color of the Pixel at the specified coordinate.
	 * If the Pixel is activated, return the corresponding palette color.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return Pixel color.
	 */
	Colors::RGB ColorCanvas::get_pixel_color(uint16_t x, uint16_t y) {
		if (in_bounds(x, y)) {
			return frames_[current_frame_index_][section_->get_dimensions()->get_inline_index(x, y)];
		}
		else {
			return {0, 0, 0};
		}
	}

	// Drawing functions
	/**
	 * Sets the color of the pixel at the specified index to the current drawing color.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 */
	void ColorCanvas::activate(uint16_t x, uint16_t y) {
		frames_[current_frame_index_][section_->get_dimensions()->get_inline_index(x, y)] = drawing_color_;
	}
	/**
	 * Sets the color of the pixel at the specified index to black.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 */
	void ColorCanvas::deactivate(uint16_t x, uint16_t y) {
		frames_[current_frame_index_][section_->get_dimensions()->get_inline_index(x, y)] = {0, 0, 0};
	}

	/**
	 * Draws a circle using the specified color.
	 * @param color Color to draw with.
	 * @param origin_x Center x coordinate.
	 * @param origin_y Center y coordinate.
	 * @param radius The circle's radius.
	 * @param fill Whether to fill the circle or leave it empty.
	 */
	void ColorCanvas::draw_circle(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		drawing_color_ = color;
		Canvas::draw_circle(origin_x, origin_y, radius, fill);
	}

	/**
	 * Draws a line using the specified color.
	 * @param color Color to draw with.
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 * @param target_x Ending point x coordinate.
	 * @param target_y Ending point y coordinate.
	 */
	void ColorCanvas::draw_line(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		drawing_color_ = color;
		Canvas::draw_line(origin_x, origin_y, target_x, target_y);
	}

	/**
	 * Draws a single pixel using the specified color.
	 * @param color Color to draw with.
	 * @param cursor_x Pixel x coordinate.
	 * @param cursor_y Pixel y coordinate.
	 */
	void ColorCanvas::draw_point(Colors::RGB color, uint16_t x, uint16_t y) {
		drawing_color_ = color;
		Canvas::draw_point(x, y);
	}

	/**
	 * Draws a rectangle using the specified color.
	 * @param color Color to draw with.
	 * @param origin_x Top-left corner x coordinate.
	 * @param origin_y Top-left corner y coordinate.
	 * @param size_x Width of the rectangle.
	 * @param size_y Height of the rectangle.
	 * @param fill Whether to fill the rectangle or leave it empty.
	 */
	void ColorCanvas::draw_rect(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		drawing_color_ = color;
		Canvas::draw_rect(origin_x, origin_y, size_x, size_y, fill);
	}

	/**
	 * Draws text using the specified color.
	 * @param color Color to draw with.
	 * @param origin_x Top-left x coordinate.
	 * @param origin_y Top-left y coordinate.
	 * @param font The Font to draw the text in.
	 * @param text The string to draw.
	 */
	void ColorCanvas::draw_text(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, Font *font, const char* text, uint8_t num_chars) {
		drawing_color_ = color;
		Canvas::draw_text(origin_x, origin_y, font, text, num_chars);
	}

	/**
	 * Draws a triangle using the specified color.
	 * @param color Color to draw with.
	 * @param point_a_x First point x-coordinate.
	 * @param point_a_y First point y-coordinate.
	 * @param point_b_x Second point x-coordinate.
	 * @param point_b_y Second point y-coordinate.
	 * @param point_c_x Third point x-coordinate.
	 * @param point_c_y Third point y-coordinate.
	 * @param fill Whether to fill the triangle or leave it empty.
	 */
	void ColorCanvas::draw_triangle(Colors::RGB color, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		drawing_color_ = color;
		Canvas::draw_triangle(point_a_x, point_a_y, point_b_x, point_b_y, point_c_x, point_c_y, fill);
	}

	/**
	 * Returns the Canvas type.
	 * @return Canvas type.
	 */
	CanvasType::Type ColorCanvas::get_type() const {
		return CanvasType::Type::ColorCanvas;
	}

	/// Builds the Canvas.
	void ColorCanvas::initialize() {
		frames_ = new Colors::RGB*[num_frames_];
		for (uint16_t i = 0; i < num_frames_; i++) {
			frames_[i] = new Colors::RGB[section_->get_dimensions()->size()];
			for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
				frames_[i][pixel] = {0, 0, 0};
			}
		}
	}

	ColorCanvas::~ColorCanvas() {
		delete_frames();
	}
}
