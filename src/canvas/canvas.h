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
			/// Defines the scrolling behavior of a Canvas.
			struct Scroll {
				/// The direction and rate that the Canvas will scroll along the x-axis.
				signed short interval_x = 0;
				/// The direction and rate that the Canvas will scroll along the y-axis.
				signed short interval_y = 0;

				/// The last time the Canvas scrolled along the x-axis.
				unsigned long last_scroll_x = 0;
				/// The last time the Canvas scrolled along the y-axis.
				unsigned long last_scroll_y = 0;

				/// Whether to repeat the Pattern while scrolling over the grid.
				bool repeat = false;

				/**
				 * Constructor. Sets the scroll rate and direction.
				 * @param x Scrolling along the x-axis.
				 * @param y Scrolling along the y-axis.
				 * @param repeat If true, repeat the Canvas while scrolling.
				 */
				Scroll(signed short x, signed short y, bool repeat) {
					this->interval_x = x;
					this->interval_y = y;
					this->repeat = repeat;
				}

			};

			Canvas(Section* section);
			void clear();
			void draw_circle(unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void draw_line(unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void draw_point(unsigned short x, unsigned short y);
			void draw_rect(unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			void draw_text(unsigned short origin_x, unsigned short origin_y, Font* font, const char* text);
			void draw_triangle(unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);
			void erase(unsigned short x, unsigned short y);
			bool* get_pattern();
			bool get_pattern_index(unsigned int index);
			Section* get_section();
			bool in_bounds(Point* point);
			bool in_bounds(unsigned short x, unsigned short y);
			void initialize_pattern();
			void remove_scroll();
			void set_scroll(signed short x, signed short y, bool repeat);
			void set_section(Section* section_);
			void set_offset(signed short x, signed short y);
			void update(const unsigned long& current_time);
			void update_scroll(const unsigned long& current_time);
			~Canvas();

		private:
			/// How far the Canvas is offset from the Pixel grid origin.
			signed int offset_x_ = 0;
			signed int offset_y_ = 0;

			/**
				The pattern to display.
				Stored as an array of booleans where 'true' indicates a drawn Pixel.
			*/
			bool* pattern_ = nullptr;

			/// The scrolling behavior of the Canvas.
			Scroll* scroll_ = nullptr;

			/**
			 * The Canvas' parent Section.
			 * This is automatically set after using Section::set_canvas().
			 */
			Section* section_ = nullptr;
	};
}

#endif // CANVAS_H
