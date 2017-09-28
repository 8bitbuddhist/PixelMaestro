#ifndef CANVASCUE_H
#define CANVASCUE_H

#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class CanvasCue : public Cue {
		public:
			enum Action {
				DrawCircle,
				DrawLine,
				DrawPoint,
				DrawRect,
				DrawText,
				DrawTriangle
			};

			enum Bit {
				ComponentBit = CueController::Bit::PayloadBit,
				ActionBit,
				TypeBit,
				SectionBit,
				OptionsBit
			};

			CanvasCue(Maestro* maestro, unsigned char* buffer) : Cue(maestro, buffer) {}
			void draw_circle(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void draw_circle(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void draw_line(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void draw_line(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void draw_point(unsigned char section_num, unsigned short x, unsigned short y);
			void draw_point(unsigned char section_num, Colors::RGB color, unsigned short x, unsigned short y);
			void draw_rect(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			void draw_rect(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			void draw_text(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char* text, unsigned char num_chars);
			void draw_text(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char* text, unsigned char num_chars);
			void draw_triangle(unsigned char section_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);
			void draw_triangle(unsigned char section_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);

			void run(unsigned char* cue);
	};
}

#endif // CANVASCUE_H
