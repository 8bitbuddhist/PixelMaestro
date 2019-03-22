/*
 * Canvas.h - Base class for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include "../core/colors.h"
#include "../core/point.h"
#include "../core/section.h"
#include "../core/timer/timer.h"
#include "fonts/font.h"

namespace PixelMaestro {
	class Section;
	class Timer;

	class Canvas {
		public:
			explicit Canvas(Section *section, uint16_t num_frames = 1);
			~Canvas();
			Colors::RGB* get_pixel_color(uint16_t x, uint16_t y);
			void initialize();

			void clear();
			void draw_circle(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			void draw_frame(uint8_t* frame, uint16_t size_x, uint16_t size_y);
			void draw_line(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			void draw_point(uint8_t color_index, uint16_t x, uint16_t y);
			void draw_rect(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			void draw_text(uint8_t color_index, uint16_t origin_x, uint16_t origin_y, Font* font, const char* text, uint8_t num_chars);
			void draw_triangle(uint8_t color_index, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);
			void erase_point(uint16_t x, uint16_t y);
			uint16_t get_current_frame_index() const;
			Timer* get_frame_timer() const;
			uint8_t* get_frame(uint16_t frame) const;
			uint16_t get_num_frames() const;
			Palette* get_palette() const;
			Section* get_section() const;
			void next_frame();
			void previous_frame();
			void remove_frame_timer();
			void set_current_frame_index(uint16_t index);
			void set_frame_timer(uint16_t speed);
			void set_num_frames(uint16_t num_frames);
			void set_palette(Palette* palette);
			void update(const uint32_t& current_time);

		private:
			/// The index of the current frame.
			uint16_t current_frame_index_ = 0;

			/// Timer for frame animations.
			Timer* frame_timer_ = nullptr;

			/**
			 * The frames in the Canvas.
			 * Each frame consists the index of a color in the palette.
			 */
			uint8_t** frames_ = nullptr;

			/// The number of frames.
			uint16_t num_frames_ = 0;

			/// Color palette used in the Canvas.
			Palette* palette_ = nullptr;

			/**
			 * The Canvas' parent Section.
			 * This is automatically set after using Section::set_canvas().
			 */
			Section* section_ = nullptr;

			void delete_frames();
	};
}

#endif // CANVAS_H
