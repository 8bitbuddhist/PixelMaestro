#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "../canvas/fonts/font5x8.h"
#include "canvascuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	void CanvasCueHandler::clear(uint8_t section_num, uint8_t overlay_num) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::Clear;
		controller_->get_cue()[Byte::TypeByte] = 255;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
	}

	void CanvasCueHandler::draw_circle(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawCircle;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 4] = radius_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 5] = radius_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 6] = (uint8_t)fill;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 7));
	}

	void CanvasCueHandler::draw_circle(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawCircle;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = color.r;
		controller_->get_cue()[Byte::OptionsByte + 1] = color.g;
		controller_->get_cue()[Byte::OptionsByte + 2] = color.b;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 7] = radius_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 8] = radius_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 9] = (uint8_t)fill;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 10));
	}

	void CanvasCueHandler::draw_frame(uint8_t section_num, uint8_t overlay_num, uint16_t size_x, uint16_t size_y, bool *frame) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawFrame;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = size_x;
		controller_->get_cue()[Byte::OptionsByte + 1] = size_y;

		uint32_t num_pixels = size_x * size_y;
		for (uint32_t pixel = 0; pixel < num_pixels; pixel++) {
			controller_->get_cue()[(Byte::OptionsByte + 2) + pixel] = (uint8_t)frame[pixel];
		}

		controller_->assemble((uint8_t)(Byte::OptionsByte + num_pixels));
	}

	void CanvasCueHandler::draw_frame(uint8_t section_num, uint8_t overlay_num, uint16_t size_x, uint16_t size_y, Colors::RGB *frame) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawFrame;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = size_x;
		controller_->get_cue()[Byte::OptionsByte + 1] = size_y;

		uint32_t options_index = 2;
		uint32_t num_pixels = size_x * size_y;
		for (uint32_t pixel = 0; pixel < num_pixels; pixel++) {
			controller_->get_cue()[Byte::OptionsByte + options_index] = frame->r;
			options_index++;
			controller_->get_cue()[Byte::OptionsByte + options_index] = frame->g;
			options_index++;
			controller_->get_cue()[Byte::OptionsByte + options_index] = frame->b;
			options_index++;
		}

		controller_->assemble((uint8_t)(Byte::OptionsByte + options_index));
	}

	void CanvasCueHandler::draw_line(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawLine;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 4] = target_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 5] = target_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 6] = target_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 7] = target_y_byte.converted_1;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 8));
	}

	void CanvasCueHandler::draw_line(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawLine;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = color.r;
		controller_->get_cue()[Byte::OptionsByte + 1] = color.g;
		controller_->get_cue()[Byte::OptionsByte + 2] = color.b;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 7] = target_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 8] = target_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 9] = target_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 10] = target_y_byte.converted_1;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 11));
	}

	void CanvasCueHandler::draw_point(uint8_t section_num, uint8_t overlay_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawPoint;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = y_byte.converted_1;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 4));
	}

	void CanvasCueHandler::draw_point(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawPoint;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = color.r;
		controller_->get_cue()[Byte::OptionsByte + 1] = color.g;
		controller_->get_cue()[Byte::OptionsByte + 2] = color.b;
		controller_->get_cue()[Byte::OptionsByte + 3] = x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 4] = x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 5] = y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 6] = y_byte.converted_1;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 7));
	}

	void CanvasCueHandler::draw_rect(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawRect;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 4] = size_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 5] = size_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 6] = size_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 7] = size_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 8] = (uint8_t)fill;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 9));
	}

	void CanvasCueHandler::draw_rect(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawRect;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = color.r;
		controller_->get_cue()[Byte::OptionsByte + 1] = color.g;
		controller_->get_cue()[Byte::OptionsByte + 2] = color.b;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 7] = size_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 8] = size_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 9] = size_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 10] = size_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 11] = (uint8_t)fill;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 12));
	}

	void CanvasCueHandler::draw_triangle(uint8_t section_num, uint8_t overlay_num, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawTriangle;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = point_a_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = point_a_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = point_a_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = point_a_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 4] = point_b_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 5] = point_b_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 6] = point_b_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 7] = point_b_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 8] = point_c_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 9] = point_c_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 10] = point_c_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 11] = point_c_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 12] = (uint8_t)fill;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 13));
	}

	void CanvasCueHandler::draw_triangle(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawTriangle;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = color.r;
		controller_->get_cue()[Byte::OptionsByte + 1] = color.g;
		controller_->get_cue()[Byte::OptionsByte + 2] = color.b;
		controller_->get_cue()[Byte::OptionsByte + 3] = point_a_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 4] = point_a_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 5] = point_a_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 6] = point_a_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 7] = point_b_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 8] = point_b_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 9] = point_b_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 10] = point_b_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 11] = point_c_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 12] = point_c_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 13] = point_c_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 14] = point_c_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 15] = (uint8_t)fill;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 16));
	}

	void CanvasCueHandler::draw_text(uint8_t section_num, uint8_t overlay_num, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawText;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 4] = (uint8_t)font;
		controller_->get_cue()[Byte::OptionsByte + 5] = num_chars;

		uint8_t text_index = Byte::OptionsByte + 6;
		for (uint8_t i = 0; i < num_chars; i++) {
			controller_->get_cue()[text_index] = text[i];
			text_index++;
		}

		controller_->assemble(text_index);
	}

	void CanvasCueHandler::draw_text(uint8_t section_num, uint8_t overlay_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::DrawText;
		controller_->get_cue()[Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = color.r;
		controller_->get_cue()[Byte::OptionsByte + 1] = color.g;
		controller_->get_cue()[Byte::OptionsByte + 2] = color.b;
		controller_->get_cue()[Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 7] = (uint8_t)font;
		controller_->get_cue()[Byte::OptionsByte + 8] = num_chars;

		uint8_t text_index = Byte::OptionsByte + 9;
		for (uint8_t i = 0; i < num_chars; i++) {
			controller_->get_cue()[text_index] = text[i];
			text_index++;
		}

		controller_->assemble(text_index);
	}

	void CanvasCueHandler::next_frame(uint8_t section_num, uint8_t overlay_num) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::NextFrame;
		controller_->get_cue()[Byte::TypeByte] = 255;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
	}

	void CanvasCueHandler::set_current_frame_index(uint8_t section_num, uint8_t overlay_num, uint16_t index) {
		IntByteConvert index_byte(index);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetCurrentFrameIndex;
		controller_->get_cue()[Byte::TypeByte] = 255;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = index_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = index_byte.converted_1;
	}

	void CanvasCueHandler::set_num_frames(uint8_t section_num, uint8_t overlay_num, uint16_t num_frames) {
		IntByteConvert num_frames_byte(num_frames);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetNumFrames;
		controller_->get_cue()[Byte::TypeByte] = 255;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = num_frames_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = num_frames_byte.converted_1;
	}

	void CanvasCueHandler::set_offset(uint8_t section_num, uint8_t overlay_num, int16_t x, int16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetOffset;
		controller_->get_cue()[Byte::TypeByte] = 255;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = y_byte.converted_1;
	}

	void CanvasCueHandler::set_scroll(uint8_t section_num, uint8_t overlay_num, int16_t x, int16_t y, bool repeat) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetScroll;
		controller_->get_cue()[Byte::TypeByte] = 255;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = y_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 4] = (uint8_t)repeat;
	}

	void CanvasCueHandler::run(uint8_t *cue) {
		Section* section = get_section(cue[Byte::SectionByte], cue[Byte::OverlayByte]);

		if (section == nullptr) return;

		switch ((CanvasType::Type)cue[Byte::TypeByte]) {
			case CanvasType::AnimationCanvas:
				{
					AnimationCanvas* canvas = static_cast<AnimationCanvas*>(section->get_canvas());
					if (canvas == nullptr) return;
					switch((Action)cue[Byte::ActionByte]) {
						case Action::DrawCircle:
							canvas->draw_circle(
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 4]),
								(bool)cue[Byte::OptionsByte + 6]);
							break;
						case Action::DrawFrame:
							{
								canvas->clear();
								Point frame_bounds(cue[Byte::OptionsByte], cue[Byte::OptionsByte + 1]);
								for (uint16_t y = 0; y < frame_bounds.y; y++) {
									for (uint16_t x = 0; x < frame_bounds.x; x++) {
										if (cue[(Byte::OptionsByte + 2) + frame_bounds.get_inline_index(x, y)] == true) {
											canvas->draw_point(x, y);
										}
									}
								}
							}
							break;
						case Action::DrawLine:
							canvas->draw_line(
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 4]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 6]));
							break;
						case Action::DrawPoint:
							canvas->draw_point(
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]));
							break;
						case Action::DrawRect:
							canvas->draw_rect(
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 4]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 6]),
								(bool)cue[Byte::OptionsByte + 8]);
							break;
						case Action::DrawText:
							{
								Font* font;
								switch ((Font::Type)cue[Byte::OptionsByte + 4]) {
									case Font::Type::Font5x8:
										font = new Font5x8();
										break;
								}

								canvas->draw_text(
									IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
									IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]),
									font,
									(char*)&cue[Byte::OptionsByte + 6],
									cue[Byte::OptionsByte + 5]
								);

								delete font;
							}
							break;
						case Action::DrawTriangle:
							canvas->draw_triangle(
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 4]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 6]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 8]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 10]),
								(bool)cue[Byte::OptionsByte + 12]);
							break;
						default:
							break;
					}
				}
				break;
			case CanvasType::ColorCanvas:
				{
					ColorCanvas* canvas = static_cast<ColorCanvas*>(section->get_canvas());
					if (canvas == nullptr) return;
					Colors::RGB color = {
						cue[Byte::OptionsByte],
						cue[Byte::OptionsByte + 1],
						cue[Byte::OptionsByte + 2]
					};
					switch((Action)cue[Byte::ActionByte]) {
						case Action::DrawCircle:
							canvas->draw_circle(
								color,
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 7]),
								bool(cue[Byte::OptionsByte + 9]));
							break;
						case Action::DrawFrame:
							{
								canvas->clear();
								uint32_t current_index = 2;
								Point frame_bounds(cue[Byte::OptionsByte], cue[Byte::OptionsByte + 1]);
								for (uint16_t y = 0; y < frame_bounds.y; y++) {
									for (uint16_t x = 0; x < frame_bounds.x; x++) {
										Colors::RGB color(cue[Byte::OptionsByte + current_index],
												cue[Byte::OptionsByte + current_index + 1],
												cue[Byte::OptionsByte + current_index + 2]);

										canvas->draw_point(color, x, y);
										current_index += 3;
									}
								}
							}
							break;
						case Action::DrawLine:
							canvas->draw_line(
								color,
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 7]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 9]));
							break;
						case Action::DrawPoint:
							canvas->draw_point(
								color,
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 5]));
							break;
						case Action::DrawRect:
							canvas->draw_rect(
								color,
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 7]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 9]),
								bool(cue[Byte::OptionsByte + 11]));
							break;
						case Action::DrawText:
							{
								Font* font;
								switch ((Font::Type)cue[Byte::OptionsByte + 7]) {
									case Font::Type::Font5x8:
										font = new Font5x8();
										break;
								}

								Colors::RGB color = {
									cue[Byte::OptionsByte],
									cue[Byte::OptionsByte + 1],
									cue[Byte::OptionsByte + 2]
								};

								canvas->draw_text(
									color,
									IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 3]),
									IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 5]),
									font,
									(char*)&cue[Byte::OptionsByte + 9],
									cue[Byte::OptionsByte + 8]
								);

								delete font;
							}
							break;
						case Action::DrawTriangle:
							canvas->draw_triangle(
								color,
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 7]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 9]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 11]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 13]),
								bool(cue[Byte::OptionsByte + 15]));
							break;
						default:
							break;
					}
				}
				break;
			default:
				{
					Canvas* canvas = section->get_canvas();
					switch((Action)cue[Byte::ActionByte]) {
						case Action::Clear:
							canvas->clear();
							break;
						case Action::NextFrame:
							canvas->next_frame();
							break;
						case Action::SetCurrentFrameIndex:
							canvas->set_current_frame_index(IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]));
							break;
						case Action::SetNumFrames:
							canvas->set_num_frames(IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]));
							break;
						case Action::SetOffset:
							canvas->set_offset(
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2])
							);
							break;
						case Action::SetScroll:
							canvas->set_scroll(
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]),
								(bool)cue[Byte::OptionsByte + 4]
							);
							break;
						default:
							break;
					}
				}
		}
	}

	CanvasCueHandler::~CanvasCueHandler() { }
}
