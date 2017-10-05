/*
 * ColorCanvas - Displays patterns using a grid of colors.
 */

#include "colorcanvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. This initializes the color palette.
	 * @param section The Canvas' parent Section.
	 * @param colors The color palette to use.
	 */
	ColorCanvas::ColorCanvas(Section* section) : Canvas(section) {
		initialize_pattern();
	}

	/**
	 * Returns the color of the Pixel at the specified index.
	 * If the Pixel is activated, return the Color at the specified index in the palette
	 * @param pixel
	 * @return
	 */
	Colors::RGB ColorCanvas::get_pixel_color(uint32_t pixel) {
		return color_pattern_[pixel];
	}

	// Drawing functions
	/**
	 * Sets the color of the pixel at the specified index to the current drawing color.
	 * @param pixel Pixel to activate.
	 */
	void ColorCanvas::activate(uint32_t pixel) {
		color_pattern_[pixel] = drawing_color_;
	}
	/**
	 * Sets the color of the pixel at the specified index to black.
	 * @param pixel Pixel to activate.
	 */
	void ColorCanvas::deactivate(uint32_t pixel) {
		color_pattern_[pixel] = Colors::BLACK;
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
	CanvasType::Type ColorCanvas::get_type() {
		return CanvasType::Type::ColorCanvas;
	}

	/**
	 * Reinitializes the color pattern array.
	 */
	void ColorCanvas::initialize_pattern() {
		if (color_pattern_ != nullptr) {
			delete[] color_pattern_;
		}
		color_pattern_ = new Colors::RGB[section_->get_dimensions()->size()] {Colors::BLACK};
	}

	ColorCanvas::~ColorCanvas() {
		delete[] color_pattern_;
		color_pattern_ = nullptr;
	}
}
