/*
 * Canvas.h - Utilities for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "canvas/fonts/font.h"
#include "colors.h"
#include "point.h"
#include "section.h"

namespace PixelMaestro {
	class Section;

	class Canvas {
		public:

			/// The background color of the Canvas.
			Colors::RGB* bg_color = nullptr;

			/// The foregound color of the Canvas.
			Colors::RGB* fg_color = nullptr;

			/// How far the Canvas is offset from the Pixel grid origin.
			Point* offset = nullptr;

			/**
			 * The Canvas' parent Section.
			 * This is automatically set after using Section::setCanvas().
			 */
			Section* parent_section = nullptr;

			/**
				The pattern to display.
				Stored as an array of booleans where 'true' indicates an active Pixel.
			*/
			bool* pattern = nullptr;

			/// Whether to repeat the Pattern over the grid (requires scrollRate to be set).
			bool repeat = false;

			/**
			 * Direction and rate to scroll the Canvas.
			 * Scroll time is determined by the Section refresh rate * the scroll interval.
			 * Setting an axis to 0 (default) disables scrolling on that axis.
			 */
			Point* scroll_interval = nullptr;

			/// The last time the Canvas scrolled.
			unsigned long last_scroll_x, last_scroll_y = 0;

			Canvas(bool* pattern);
			void clear();
			void draw_char(Point* origin, Font* font, const char character);
			void draw_circle(Point* origin, unsigned short radius, bool fill);
			void draw_line(Point* origin, Point* target);
			void draw_rect(Point* origin, Point* size, bool fill);
			void draw_text(Point* origin, Font* font, const char* text, unsigned int num_chars);
			void draw_triangle(Point* point_a, Point* point_b, Point* point_c, bool fill);
			bool in_bounds(Point* point);
			void scroll(const unsigned long& current_time);
			void toggle_pixel(Point* coordinate);
			void update(const unsigned long& current_time);
			~Canvas();
	};
}

#endif // CANVAS_H
