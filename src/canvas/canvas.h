/*
 * Canvas.h - Base class for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include "../core/colors.h"
#include "../core/point.h"
#include "../core/section.h"
#include "../core/timing.h"
#include "fonts/font.h"
#include "canvastype.h"

namespace PixelMaestro {
	class Section;

	class Canvas {
		public:
			/// Defines the scrolling behavior of a Canvas.
			struct Scroll {
				/// The direction and rate that the Canvas will scroll along the x-axis.
				int16_t interval_x = 0;
				/// The direction and rate that the Canvas will scroll along the y-axis.
				int16_t interval_y = 0;

				/// The last time the Canvas scrolled along the x-axis.
				uint32_t last_scroll_x = 0;
				/// The last time the Canvas scrolled along the y-axis.
				uint32_t last_scroll_y = 0;

				/// Whether to repeat the Pattern while scrolling over the grid.
				bool repeat = false;

				/**
				 * Constructor. Sets the scroll rate and direction.
				 * @param x Scrolling along the x-axis.
				 * @param y Scrolling along the y-axis.
				 * @param repeat If true, repeat the Canvas while scrolling.
				 */
				Scroll(int16_t x, int16_t y, bool repeat) {
					this->interval_x = x;
					this->interval_y = y;
					this->repeat = repeat;
				}

			};

			// Virtual functions - must be implemented in derived Canvases.
			virtual ~Canvas();
			virtual void activate(uint32_t pixel) = 0;
			virtual void deactivate(uint32_t pixel) = 0;
			virtual Colors::RGB get_pixel_color(uint16_t x, uint16_t y) = 0;
			virtual CanvasType::Type get_type() = 0;
			virtual void initialize() = 0;

			Canvas(Section* section);
			Canvas(Section* section, uint16_t num_frames);
			void clear();
			void draw_circle(uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			void draw_line(uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			void draw_point(uint16_t x, uint16_t y);
			void draw_rect(uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			void draw_text(uint16_t origin_x, uint16_t origin_y, Font* font, const char* text, uint8_t num_chars);
			void draw_triangle(uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);
			void erase(uint16_t x, uint16_t y);
			uint16_t get_current_frame_index();
			uint16_t get_num_frames();
			Section* get_section();
			bool in_bounds(Point* point);
			bool in_bounds(uint32_t pixel);
			bool in_bounds(uint16_t x, uint16_t y);
			void next_frame();
			void remove_frame_timing();
			void remove_scroll();
			void set_current_frame_index(uint16_t index);
			void set_frame_timing(uint16_t speed);
			void set_num_frames(uint16_t num_frames);
			void set_offset(int16_t x, int16_t y);
			void set_scroll(int16_t x, int16_t y, bool repeat);
			void set_section(Section* section_);
			void update(const uint32_t& current_time);
			void update_scroll(const uint32_t& current_time);

		protected:
			/// The index of the current frame.
			uint16_t current_frame_index_ = 0;

			/// Controls timings for frame animations.
			Timing* frame_timing_ = nullptr;

			/// The number of frames.
			uint16_t num_frames_ = 0;

			/// How far the Canvas is offset from the Pixel grid origin.
			int16_t offset_x_ = 0;
			int16_t offset_y_ = 0;

			/// The scrolling behavior of the Canvas.
			Scroll* scroll_ = nullptr;

			/**
			 * The Canvas' parent Section.
			 * This is automatically set after using Section::set_canvas().
			 */
			Section* section_ = nullptr;

			virtual void delete_frames() = 0;
	};
}

#endif // CANVAS_H
