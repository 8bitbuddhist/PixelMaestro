/*
 * PaletteCanvas - Displays patterns using a pre-defined palette.
 */

#include "palettecanvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. Initializes the Canvas with a single frame.
	 * @param section Parent Section.
	 * @param colors Color palette.
	 * @param num_colors Number of colors in the palette.
	 */
	PaletteCanvas::PaletteCanvas(Section* section, Colors::RGB* colors, uint8_t num_colors) : Canvas(section) {
		set_colors(colors, num_colors);
		initialize();
	}

	/**
	 * Constructor. Initializes the Canvas with the specified number of frames.
	 * @param section Parent Section.
	 * @param num_frames Number of frames.
	 * @param colors Color palette.
	 * @param num_colors Number of colors in the palette.
	 */
	PaletteCanvas::PaletteCanvas(Section *section, uint16_t num_frames, Colors::RGB* colors, uint8_t num_colors) : Canvas(section, num_frames) {
		set_colors(colors, num_colors);
		initialize();
	}

	/**
	 * Deletes the current frame set.
	 */
	void PaletteCanvas::delete_frames() {
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
	void PaletteCanvas::draw_frame(uint8_t* frame, uint16_t size_x, uint16_t size_y) {
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
	uint8_t* PaletteCanvas::get_frame(uint16_t frame) const {
		return frames_[frame];
	}

	/**
	 * Returns the color of the Pixel at the specified coordinate.
	 * If the Pixel is activated, return the corresponding palette color.
	 * If the palette index of the Pixel is 255, return black.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return Pixel color.
	 */
	Colors::RGB PaletteCanvas::get_pixel_color(uint16_t x, uint16_t y) {
		if (in_bounds(x, y)) {
			uint8_t index = frames_[current_frame_index_][section_->get_dimensions()->get_inline_index(x, y)];

			if (index < num_colors_) {
				return colors_[index];
			}
		}

		return {0, 0, 0};
	}

	// Drawing functions
	/**
	 * Sets the color of the pixel at the specified index to the current drawing color.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 */
	void PaletteCanvas::activate(uint16_t x, uint16_t y) {
		frames_[current_frame_index_][section_->get_dimensions()->get_inline_index(x, y)] = drawing_color_index_;
	}
	/**
	 * Sets the color of the pixel at the specified index to black.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 */
	void PaletteCanvas::deactivate(uint16_t x, uint16_t y) {
		frames_[current_frame_index_][section_->get_dimensions()->get_inline_index(x, y)] = 255;
	}

	/**
	 * Draws a circle using the specified color.
	 * @param color_index Index of the color to draw with. Setting this to an invalid index draws black.
	 * @param origin_x Center x coordinate.
	 * @param origin_y Center y coordinate.
	 * @param radius The circle's radius.
	 * @param fill Whether to fill the circle or leave it empty.
	 */
	void PaletteCanvas::draw_circle(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		drawing_color_index_ = color_index;
		Canvas::draw_circle(origin_x, origin_y, radius, fill);
	}

	/**
	 * Draws a line using the specified color.
	 * @param color_index Index of the color to draw with. Setting this to an invalid index draws black.
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 * @param target_x Ending point x coordinate.
	 * @param target_y Ending point y coordinate.
	 */
	void PaletteCanvas::draw_line(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		drawing_color_index_ = color_index;
		Canvas::draw_line(origin_x, origin_y, target_x, target_y);
	}

	/**
	 * Draws a single pixel using the specified color.
	 * @param color_index Index of the color to draw with. Setting this to an invalid index draws black.
	 * @param cursor_x Pixel x coordinate.
	 * @param cursor_y Pixel y coordinate.
	 */
	void PaletteCanvas::draw_point(uint8_t color_index, uint16_t x, uint16_t y) {
		drawing_color_index_ = color_index;
		Canvas::draw_point(x, y);
	}

	/**
	 * Draws a rectangle using the specified color.
	 * @param color_index Index of the color to draw with. Setting this to an invalid index draws black.
	 * @param origin_x Top-left corner x coordinate.
	 * @param origin_y Top-left corner y coordinate.
	 * @param size_x Width of the rectangle.
	 * @param size_y Height of the rectangle.
	 * @param fill Whether to fill the rectangle or leave it empty.
	 */
	void PaletteCanvas::draw_rect(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		drawing_color_index_ = color_index;
		Canvas::draw_rect(origin_x, origin_y, size_x, size_y, fill);
	}

	/**
	 * Draws text using the specified color.
	 * @param color_index Index of the color to draw with. Setting this to an invalid index draws black.
	 * @param origin_x Top-left x coordinate.
	 * @param origin_y Top-left y coordinate.
	 * @param font The Font to draw the text in.
	 * @param text The string to draw.
	 */
	void PaletteCanvas::draw_text(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, Font *font, const char* text, uint8_t num_chars) {
		drawing_color_index_ = color_index;
		Canvas::draw_text(origin_x, origin_y, font, text, num_chars);
	}

	/**
	 * Draws a triangle using the specified color.
	 * @param color_index Index of the color to draw with. Setting this to an invalid index draws black.
	 * @param point_a_x First point x-coordinate.
	 * @param point_a_y First point y-coordinate.
	 * @param point_b_x Second point x-coordinate.
	 * @param point_b_y Second point y-coordinate.
	 * @param point_c_x Third point x-coordinate.
	 * @param point_c_y Third point y-coordinate.
	 * @param fill Whether to fill the triangle or leave it empty.
	 */
	void PaletteCanvas::draw_triangle(uint8_t color_index, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		drawing_color_index_ = color_index;
		Canvas::draw_triangle(point_a_x, point_a_y, point_b_x, point_b_y, point_c_x, point_c_y, fill);
	}

	/**
	 * Searches for the color in the palette, and if found returns the index of the first match.
	 * @param color Color to search for.
	 * @return Index in the palette (or 255 if not found).
	 */
	uint8_t PaletteCanvas::get_color_index(Colors::RGB *color) const {
		for (uint8_t index = 0; index < num_colors_; index++) {
			if (*color == colors_[index]) {
				return index;
			}
		}

		return 255;
	}

	/**
	 * Returns the color palette.
	 * @return Color palette.
	 */
	Colors::RGB* PaletteCanvas::get_colors() const {
		return colors_;
	}

	/**
	 * Returns the Canvas type.
	 * @return Canvas type.
	 */
	CanvasType::Type PaletteCanvas::get_type() const {
		return CanvasType::Type::PaletteCanvas;
	}

	/// Builds the Canvas.
	void PaletteCanvas::initialize() {
		frames_ = new uint8_t*[num_frames_];
		for (uint16_t frame = 0; frame < num_frames_; frame++) {
			frames_[frame] = new uint8_t[section_->get_dimensions()->size()];
			for (uint32_t pixel = 0; pixel < section_->get_dimensions()->size(); pixel++) {
				frames_[frame][pixel] = 255;
			}
		}
	}

	/**
	 * Sets the Canvas' palette.
	 * @param colors Palette colors.
	 * @param num_colors Number of colors in the palette.
	 */
	void PaletteCanvas::set_colors(Colors::RGB *colors, uint8_t num_colors) {
		this->colors_ = colors;
		this->num_colors_ = num_colors;
	}

	PaletteCanvas::~PaletteCanvas() {
		delete_frames();
	}
}