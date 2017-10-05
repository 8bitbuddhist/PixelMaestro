#ifndef CANVASCUEHANDLER_H
#define CANVASCUEHANDLER_H

#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class CanvasCueHandler : public CueHandler {
		public:
			enum Action : uint8_t {
				DrawCircle,
				DrawLine,
				DrawPoint,
				DrawRect,
				DrawText,
				DrawTriangle
			};

			enum Byte : uint8_t {
				HandlerByte = CueController::Byte::PayloadByte,
				ActionByte,
				TypeByte,
				SectionByte,
				OverlayByte,
				OptionsByte
			};

			CanvasCueHandler(CueController* controller) : CueHandler(controller) { }
			~CanvasCueHandler();
			void draw_circle(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			void draw_circle(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			void draw_line(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			void draw_line(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			void draw_point(uint8_t section_num, uint8_t overlay_num, uint16_t x, uint16_t y);
			void draw_point(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t x, uint16_t y);
			void draw_rect(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			void draw_rect(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			void draw_text(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars);
			void draw_text(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars);
			void draw_triangle(uint8_t section_num, uint8_t overlay_num, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);
			void draw_triangle(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);

			void run(uint8_t* cue);
	};
}

#endif // CANVASCUEHANDLER_H
