/*
 * ColorCanvas - Displays patterns using a grid of colors.
 */

#ifndef COLORCANVAS_H
#define COLORCANVAS_H

#include "basecanvas.h"

namespace PixelMaestro {
	class ColorCanvas : public BaseCanvas {
		public:
			ColorCanvas(Section* section);
			~ColorCanvas();
			Colors::RGB get_pixel_color(unsigned int pixel);
			void initialize_pattern();

			// Overriden functions
			void activate(unsigned int pixel);
			void deactivate(unsigned int pixel);
			void draw_circle(Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void draw_line(Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void draw_point(Colors::RGB color, unsigned short x, unsigned short y);
			void draw_rect(Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			void draw_text(Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font* font, const char* text);
			void draw_triangle(Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);

		private:
			/**
			 * The pattern to display.
			 * Stored as an array of Color::RGB values, which are drawn directly to the Pixel.
			*/
			Colors::RGB* color_pattern_ = nullptr;

			/// Stores the color currently being used to draw a pattern.
			Colors::RGB drawing_color_ = Colors::BLACK;
	};
}

#endif // COLORCANVAS_H
