/*
 * ColorCanvas - Displays patterns using a grid of colors.
 */

#ifndef COLORCANVAS_H
#define COLORCANVAS_H

#include "canvas.h"

namespace PixelMaestro {
	class ColorCanvas : public Canvas {
		public:
			ColorCanvas(Section* section);
			~ColorCanvas();
			Colors::RGB get_pixel_color(uint32_t pixel);
			void initialize_pattern();

			// Overriden functions
			void activate(uint32_t pixel);
			void deactivate(uint32_t pixel);
			void draw_circle(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			void draw_line(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			void draw_point(Colors::RGB color, uint16_t x, uint16_t y);
			void draw_rect(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			void draw_text(Colors::RGB color, uint16_t origin_x, uint16_t origin_y, Font* font, const char* text, uint8_t num_chars);
			void draw_triangle(Colors::RGB color, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);
			CanvasType::Type get_type();

		private:
			/**
			 * The pattern to display.
			 * Stored as an array of Color::RGB values, which are drawn directly to the Pixel.
			*/
			Colors::RGB* color_pattern_ = nullptr;

			/// Stores the color currently being used to draw shapes.
			Colors::RGB drawing_color_ = Colors::BLACK;
	};
}

#endif // COLORCANVAS_H
