/*
 * PaletteCanvas - Displays patterns using a pre-defined palette.
 */

#ifndef PALETTECANVAS_H
#define PALETTECANVAS_H

#include "canvas.h"

namespace PixelMaestro {
	class PaletteCanvas : public Canvas {
		public:
			PaletteCanvas(Section* section, Colors::RGB* colors, uint8_t num_colors);
			PaletteCanvas(Section *section, uint16_t num_frames, Colors::RGB* colors, uint8_t num_colors);
			~PaletteCanvas();
			Colors::RGB get_pixel_color(uint16_t x, uint16_t y);

			// Overriden functions
			void activate(uint16_t x, uint16_t y);
			void deactivate(uint16_t x, uint16_t y);
			void draw_circle(uint8_t color, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			void draw_frame(uint8_t* frame, uint16_t size_x, uint16_t size_y);
			void draw_line(uint8_t color, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			void draw_point(uint8_t color, uint16_t x, uint16_t y);
			void draw_rect(uint8_t color, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			void draw_text(uint8_t color, uint16_t origin_x, uint16_t origin_y, Font* font, const char* text, uint8_t num_chars);
			void draw_triangle(uint8_t color, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);
			uint8_t get_color_index(Colors::RGB* color);
			uint8_t* get_frame(uint16_t frame) const;
			CanvasType::Type get_type() const;
			void initialize();
			void set_colors(Colors::RGB* colors, uint8_t num_colors);

		protected:
			void delete_frames();

		private:
			/// The color palette.
			Colors::RGB* colors_ = nullptr;

			/// The index of the color currently being used to draw shapes.
			uint8_t drawing_color_index_;

			/**
			 * The frames in the Canvas.
			 * Each frame consists the index of a color in the palette.
			 */
			uint8_t** frames_ = nullptr;

			/// The number of colors in the palette.
			uint8_t num_colors_	= 0;
	};
}

#endif // PALETTECANVAS_H