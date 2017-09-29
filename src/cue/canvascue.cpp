#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "../canvas/fonts/font5x8.h"
#include "canvascuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	void CanvasCueHandler::draw_circle(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawCircle;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::AnimationCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 4] = radius_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 5] = radius_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 6] = (unsigned char)fill;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 7));
	}

	void CanvasCueHandler::draw_circle(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawCircle;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::ColorCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = color.r;
		controller_->get_cue()[Bit::OptionsBit + 1] = color.g;
		controller_->get_cue()[Bit::OptionsBit + 2] = color.b;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 7] = radius_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 8] = radius_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 9] = (unsigned char)fill;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 10));
	}

	void CanvasCueHandler::draw_line(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawLine;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::AnimationCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 4] = target_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 5] = target_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 6] = target_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 7] = target_y_byte.converted_1;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 8));
	}

	void CanvasCueHandler::draw_line(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawLine;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::ColorCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = color.r;
		controller_->get_cue()[Bit::OptionsBit + 1] = color.g;
		controller_->get_cue()[Bit::OptionsBit + 2] = color.b;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 7] = target_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 8] = target_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 9] = target_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 10] = target_y_byte.converted_1;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 11));
	}

	void CanvasCueHandler::draw_point(unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawPoint;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::AnimationCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = y_byte.converted_1;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 4));
	}

	void CanvasCueHandler::draw_point(unsigned char section_num, Colors::RGB color, unsigned short x, unsigned short y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawPoint;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::AnimationCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = color.r;
		controller_->get_cue()[Bit::OptionsBit + 1] = color.g;
		controller_->get_cue()[Bit::OptionsBit + 2] = color.b;
		controller_->get_cue()[Bit::OptionsBit + 3] = x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 4] = x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 5] = y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 6] = y_byte.converted_1;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 7));
	}

	void CanvasCueHandler::draw_rect(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawRect;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::AnimationCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 4] = size_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 5] = size_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 6] = size_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 7] = size_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 8] = (unsigned char)fill;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 9));
	}

	void CanvasCueHandler::draw_rect(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawRect;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::ColorCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = color.r;
		controller_->get_cue()[Bit::OptionsBit + 1] = color.g;
		controller_->get_cue()[Bit::OptionsBit + 2] = color.b;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 7] = size_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 8] = size_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 9] = size_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 10] = size_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 11] = (unsigned char)fill;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 12));
	}

	void CanvasCueHandler::draw_triangle(unsigned char section_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawTriangle;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::AnimationCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = point_a_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = point_a_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = point_a_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = point_a_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 4] = point_b_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 5] = point_b_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 6] = point_b_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 7] = point_b_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 8] = point_c_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 9] = point_c_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 10] = point_c_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 11] = point_c_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 12] = (unsigned char)fill;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 13));
	}

	void CanvasCueHandler::draw_triangle(unsigned char section_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawTriangle;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::ColorCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = color.r;
		controller_->get_cue()[Bit::OptionsBit + 1] = color.g;
		controller_->get_cue()[Bit::OptionsBit + 2] = color.b;
		controller_->get_cue()[Bit::OptionsBit + 3] = point_a_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 4] = point_a_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 5] = point_a_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 6] = point_a_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 7] = point_b_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 8] = point_b_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 9] = point_b_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 10] = point_b_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 11] = point_c_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 12] = point_c_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 13] = point_c_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 14] = point_c_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 15] = (unsigned char)fill;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 16));
	}

	void CanvasCueHandler::draw_text(unsigned char section_num, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawText;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::AnimationCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 4] = (unsigned char)font;
		controller_->get_cue()[Bit::OptionsBit + 5] = num_chars;

		unsigned char text_index = Bit::OptionsBit + 6;
		for (unsigned char i = 0; i < num_chars; i++) {
			controller_->get_cue()[text_index] = text[i];
			text_index++;
		}

		controller_->assemble(text_index);
	}

	void CanvasCueHandler::draw_text(unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::CanvasHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::DrawText;
		controller_->get_cue()[Bit::TypeBit] = (unsigned char)CanvasType::ColorCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = color.r;
		controller_->get_cue()[Bit::OptionsBit + 1] = color.g;
		controller_->get_cue()[Bit::OptionsBit + 2] = color.b;
		controller_->get_cue()[Bit::OptionsBit + 3] = origin_x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 4] = origin_x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 5] = origin_y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 6] = origin_y_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 7] = (unsigned char)font;
		controller_->get_cue()[Bit::OptionsBit + 8] = num_chars;

		unsigned char text_index = Bit::OptionsBit + 9;
		for (unsigned char i = 0; i < num_chars; i++) {
			controller_->get_cue()[text_index] = text[i];
			text_index++;
		}

		controller_->assemble(text_index);
	}

	void CanvasCueHandler::run(unsigned char *cue) {
		CanvasType::Type canvas_type = (CanvasType::Type)cue[Bit::TypeBit];
		if (canvas_type == CanvasType::AnimationCanvas) {
			AnimationCanvas* canvas = static_cast<AnimationCanvas*>(controller_->get_maestro()->get_section(cue[Bit::SectionBit])->get_canvas());
			switch((Action)cue[Bit::ActionBit]) {
				case Action::DrawCircle:
					canvas->draw_circle(
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 4]),
						(bool)cue[Bit::OptionsBit + 6]);
					break;
				case Action::DrawLine:
					canvas->draw_line(
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 4]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 6]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 4]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 6]),
						(bool)cue[Bit::OptionsBit + 8]);
					break;
				case Action::DrawText:
					{
						// TODO: There must be a better way to handle this.
						Font* font;
						switch ((Font::Type)cue[Bit::OptionsBit + 4]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						canvas->draw_text(
							IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]),
							IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]),
							font,
							(char*)&cue[Bit::OptionsBit + 6],
							cue[Bit::OptionsBit + 5]
						);

						delete font;
					}
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 4]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 6]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 8]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 10]),
						(bool)cue[Bit::OptionsBit + 12]);
					break;
			}
		}
		else if (canvas_type == CanvasType::ColorCanvas) {
			ColorCanvas* canvas = static_cast<ColorCanvas*>(controller_->get_maestro()->get_section(cue[Bit::SectionBit])->get_canvas());
			Colors::RGB color = {
				cue[Bit::OptionsBit],
				cue[Bit::OptionsBit + 1],
				cue[Bit::OptionsBit + 2]
			};
			switch((Action)cue[Bit::ActionBit]) {
				case Action::DrawCircle:
					canvas->draw_circle(
						color,
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 3]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 5]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 7]),
						bool(cue[Bit::OptionsBit + 9]));
					break;
				case Action::DrawLine:
					canvas->draw_line(
						color,
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 3]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 5]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 7]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 11]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						color,
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 3]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 5]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						color,
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 3]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 5]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 7]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 9]),
						bool(cue[Bit::OptionsBit + 11]));
					break;
				case Action::DrawText:
					{
						// See AnimationCanvas::DrawText
						Font* font;
						switch ((Font::Type)cue[Bit::OptionsBit + 7]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						Colors::RGB color = {
							cue[Bit::OptionsBit],
							cue[Bit::OptionsBit + 1],
							cue[Bit::OptionsBit + 2]
						};

						canvas->draw_text(
							color,
							IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 3]),
							IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 5]),
							font,
							(char*)&cue[Bit::OptionsBit + 9],
							cue[Bit::OptionsBit + 8]
						);

						delete font;
					}
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						color,
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 3]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 5]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 7]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 9]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 11]),
						IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 13]),
						bool(cue[Bit::OptionsBit + 15]));
					break;
			}
		}
	}
}
