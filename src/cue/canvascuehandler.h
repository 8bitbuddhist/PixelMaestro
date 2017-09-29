#ifndef CANVASCUEHANDLER_H
#define CANVASCUEHANDLER_H

#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class CanvasCueHandler : public CueHandler {
		public:
			enum Action {
				DrawCircle,
				DrawLine,
				DrawPoint,
				DrawRect,
				DrawText,
				DrawTriangle
			};

			enum Byte {
				HandlerByte = CueController::Byte::PayloadByte,
				ActionByte,
				TypeByte,
				SectionByte,
				OverlayByte,
				OptionsByte
			};

			CanvasCueHandler(CueController* controller) : CueHandler(controller) { }
			~CanvasCueHandler();
			void draw_circle(unsigned char section_num, unsigned char overlay_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void draw_circle(unsigned char section_num, unsigned char overlay_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void draw_line(unsigned char section_num, unsigned char overlay_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void draw_line(unsigned char section_num, unsigned char overlay_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void draw_point(unsigned char section_num, unsigned char overlay_num, unsigned short x, unsigned short y);
			void draw_point(unsigned char section_num, unsigned char overlay_num, Colors::RGB color, unsigned short x, unsigned short y);
			void draw_rect(unsigned char section_num, unsigned char overlay_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			void draw_rect(unsigned char section_num, unsigned char overlay_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill);
			void draw_text(unsigned char section_num, unsigned char overlay_num, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char* text, unsigned char num_chars);
			void draw_text(unsigned char section_num, unsigned char overlay_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char* text, unsigned char num_chars);
			void draw_triangle(unsigned char section_num, unsigned char overlay_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);
			void draw_triangle(unsigned char section_num, unsigned char overlay_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);

			void run(unsigned char* cue);
	};
}

#endif // CANVASCUEHANDLER_H
