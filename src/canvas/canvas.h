/*
 * Canvas.h - Utilities for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "../core/colors.h"
#include "../core/point.h"
#include "../core/section.h"
#include "fonts/font.h"

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

			/// Whether to repeat the Pattern while scrolling over the grid.
			bool repeat = false;

			/**
			 * The direction and rate that the Canvas will scroll in.
			 * Scroll time is determined by the Section refresh rate * the scroll interval, so an interval of '5' means scrolling occurs once on that axis every 5 refreshes.
			 *
			 * Setting an axis to 0 (default) disables scrolling on that axis.
			 */
			Point* scroll_interval = nullptr;

			/// The last time the Canvas scrolled.
			unsigned long last_scroll_x, last_scroll_y = 0;

			Canvas(Section* section);
			void clear();
			void draw_circle(Point* origin, unsigned short radius, bool fill);
			void draw_line(Point* origin, Point* target);
			void draw_point(Point* cursor);
			void draw_rect(Point* origin, Point* size, bool fill);
			void draw_text(Point* origin, Font* font, const char* text);
			void draw_triangle(Point* point_a, Point* point_b, Point* point_c, bool fill);
			void erase(Point* cursor);
			bool in_bounds(Point* point);
			void scroll(const unsigned long& current_time);
			void update(const unsigned long& current_time);
			~Canvas();
	};
}

#endif // CANVAS_H
