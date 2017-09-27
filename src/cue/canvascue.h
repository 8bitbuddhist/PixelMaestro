#ifndef CANVASCUE_H
#define CANVASCUE_H

#include "../core/maestro.h"

namespace PixelMaestro {
	class CanvasCue	{
		public:
			enum Action {
				DrawCircle,
				DrawLine,
				DrawPoint,
				DrawRect,
				DrawText,
				DrawTriangle
			};

			static void draw_circle(unsigned char* buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			static void draw_circle(unsigned char* buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			static void draw_line(unsigned char* buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			static void draw_line(unsigned char* buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			static void draw_point(unsigned char* buffer, unsigned char section_num, unsigned short x, unsigned short y);
			static void draw_point(unsigned char* buffer, unsigned char section_num, Colors::RGB color, unsigned short x, unsigned short y);
			static void draw_rect(unsigned char* buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			static void draw_rect(unsigned char* buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			static void draw_text(unsigned char* buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char* text, unsigned char num_chars);
			static void draw_text(unsigned char* buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char* text, unsigned char num_chars);
			static void draw_triangle(unsigned char* buffer, unsigned char section_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);
			static void draw_triangle(unsigned char* buffer, unsigned char section_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);

			static void run(Maestro* maestro, unsigned char* cue);
	};
}

#endif // CANVASCUE_H
