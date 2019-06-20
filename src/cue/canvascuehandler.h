#ifndef CANVASCUEHANDLER_H
#define CANVASCUEHANDLER_H

#include "cuecontroller.h"

namespace PixelMaestro {
	class CanvasCueHandler : public CueHandler {
		public:
			enum class Action : uint8_t {
				Clear,
				DrawCircle,
				DrawFrame,
				DrawLine,
				DrawPoint,
				DrawRect,
				DrawText,
				DrawTriangle,
				ErasePoint,
				NextFrame,
				PreviousFrame,
				RemoveFrameTimer,
				SetCurrentFrameIndex,
				OBSOLETE_SetDrawingColor,	// Replaceable
				SetFrameTimer,
				SetNumFrames,
				SetPalette,
				StartFrameTimer,
				StopFrameTimer
			};

			enum class Byte : uint8_t {
				HandlerByte = (uint8_t)CueController::Byte::PayloadByte,
				ActionByte,
				SectionByte,
				LayerByte,
				FrameByte1,
				FrameByte2,
				OptionsByte
			};

			explicit CanvasCueHandler(CueController& controller) : CueHandler(controller) { }
			~CanvasCueHandler() = default;
			uint8_t* clear(uint8_t section_num, uint8_t layer_num);
			uint8_t* draw_circle(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill);
			uint8_t* draw_frame(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint16_t size_x, uint16_t size_y, const uint8_t* frame);
			uint8_t* draw_line(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y);
			uint8_t* draw_point(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t x, uint16_t y);
			uint8_t* draw_rect(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill);
			uint8_t* draw_text(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars);
			uint8_t* draw_triangle(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint8_t color_index, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill);
			uint8_t* erase_point(uint8_t section_num, uint8_t layer_num, uint16_t frame_index, uint16_t x, uint16_t y);
			uint8_t* next_frame(uint8_t section_num, uint8_t layer_num);
			uint8_t* previous_frame(uint8_t section_num, uint8_t layer_num);
			uint8_t* remove_frame_timer(uint8_t section_num, uint8_t layer_num);
			uint8_t* set_current_frame_index(uint8_t section_num, uint8_t layer_num, uint16_t frame_index);
			uint8_t* set_frame_timer(uint8_t section_num, uint8_t layer_num, uint16_t speed);
			uint8_t* set_num_frames(uint8_t section_num, uint8_t layer_num, uint16_t num_frames);
			uint8_t* set_palette(uint8_t section_num, uint8_t layer_num, const Palette& palette);
			uint8_t* start_frame_timer(uint8_t section_num, uint8_t layer_num);
			uint8_t* stop_frame_timer(uint8_t section_num, uint8_t layer_num);

			void run(uint8_t* cue);
			uint32_t start_cue(uint8_t handler_byte, uint8_t action_byte, uint8_t section_num, uint8_t layer_num, uint16_t frame_num = 0);

		private:
			Font* get_font(Font::Type font_type);
	};
}

#endif // CANVASCUEHANDLER_H
