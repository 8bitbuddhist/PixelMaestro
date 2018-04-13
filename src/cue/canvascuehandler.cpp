#include "../canvas/canvas.h"
#include "../canvas/fonts/font5x8.h"
#include "canvascuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	uint8_t* CanvasCueHandler::clear(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::Clear;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::draw_circle(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawCircle;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = radius_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = radius_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 8);
	}

	uint8_t* CanvasCueHandler::draw_frame(uint8_t section_num, uint8_t layer_num, uint16_t size_x, uint16_t size_y, uint8_t* frame) {
		// Check the size of the buffer. If it's not big enough to store the frame, exit.
		if ((size_x * size_y) > controller_->get_buffer_size()) {
			return nullptr;
		}

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawFrame;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = size_x;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = size_y;

		uint16_t current_index = (uint8_t)Byte::OptionsByte + 2;
		Point grid(size_x, size_y);
		for (uint16_t y = 0; y < size_y; y++) {
			for (uint16_t x = 0; x < size_x; x++) {
				controller_->get_buffer()[current_index] = frame[grid.get_inline_index(x, y)];
				current_index++;
			}
		}

		return controller_->assemble(current_index);
	}

	uint8_t* CanvasCueHandler::draw_line(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawLine;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = target_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = target_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = target_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = target_y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 9);
	}

	uint8_t* CanvasCueHandler::draw_point(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawPoint;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 5);
	}

	uint8_t* CanvasCueHandler::draw_rect(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawRect;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = size_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = size_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = size_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = size_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 9] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 10);
	}

	uint8_t* CanvasCueHandler::draw_triangle(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawTriangle;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = point_a_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = point_a_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = point_a_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = point_a_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = point_b_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = point_b_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = point_b_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = point_b_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 9] = point_c_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 10] = point_c_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 11] = point_c_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 12] = point_c_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 13] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 14);
	}

	uint8_t* CanvasCueHandler::draw_text(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawText;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = (uint8_t)font;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = num_chars;

		uint8_t text_index = (uint8_t)Byte::OptionsByte + 7;
		for (uint8_t i = 0; i < num_chars; i++) {
			controller_->get_buffer()[text_index] = text[i];
			text_index++;
		}

		return controller_->assemble(text_index);
	}

	uint8_t* CanvasCueHandler::erase_point(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::ErasePoint;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	uint8_t* CanvasCueHandler::next_frame(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::NextFrame;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::previous_frame(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::PreviousFrame;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::remove_frame_timer(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::RemoveFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::set_current_frame_index(uint8_t section_num, uint8_t layer_num, uint16_t index) {
		IntByteConvert index_byte(index);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetCurrentFrameIndex;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = index_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = index_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* CanvasCueHandler::set_drawing_color(uint8_t section_num, uint8_t layer_num, uint8_t color_index) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetDrawingColor;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 1);
	}

	uint8_t* CanvasCueHandler::set_frame_timer(uint8_t section_num, uint8_t layer_num, uint16_t speed) {
		IntByteConvert speed_byte(speed);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = speed_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = speed_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* CanvasCueHandler::set_num_frames(uint8_t section_num, uint8_t layer_num, uint16_t num_frames) {
		IntByteConvert num_frames_byte(num_frames);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetNumFrames;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = num_frames_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = num_frames_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* CanvasCueHandler::set_palette(uint8_t section_num, uint8_t layer_num, Palette* palette) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetPalette;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = palette->get_num_colors();

		uint16_t final_index = serialize_palette(&controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1], palette);

		return controller_->assemble(final_index + (uint8_t)Byte::OptionsByte + 1);
	}

	uint8_t* CanvasCueHandler::start_frame_timer(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::StartFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::stop_frame_timer(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::StopFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	Font* CanvasCueHandler::get_font(Font::Type font_type) {
		Font* font = nullptr;
		switch (font_type) {
			case Font::Type::Font5x8:
				font = new Font5x8();
				break;
		}
		return font;
	}

	void CanvasCueHandler::run(uint8_t *cue) {
		Section* section = get_section(cue[(uint8_t)Byte::SectionByte], cue[(uint8_t)Byte::LayerByte]);

		if (section == nullptr) return;

		Canvas* canvas = section->get_canvas();
		if (canvas == nullptr) return;

		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::Clear:
				canvas->clear();
				break;
			case Action::DrawCircle:
				canvas->draw_circle(
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
					(bool)cue[(uint8_t)Byte::OptionsByte + 7]);
				break;
			case Action::DrawFrame:
				{
					Point frame_bounds(cue[(uint8_t)Byte::OptionsByte], cue[(uint8_t)Byte::OptionsByte + 1]);
					for (uint16_t y = 0; y < frame_bounds.y; y++) {
						for (uint16_t x = 0; x < frame_bounds.x; x++) {
							canvas->draw_point(cue[(uint8_t)Byte::OptionsByte + 2 + frame_bounds.get_inline_index(x, y)], x, y);
						}
					}
				}
				break;
			case Action::DrawLine:
				canvas->draw_line(
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]));
				break;
			case Action::DrawPoint:
				canvas->draw_point(
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]));
				break;
			case Action::DrawRect:
				canvas->draw_rect(
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]),
					(bool)cue[(uint8_t)Byte::OptionsByte + 9]);
				break;
			case Action::DrawText:
				{
					Font* font = get_font((Font::Type)cue[(uint8_t)Byte::OptionsByte + 5]);

					canvas->draw_text(
						cue[(uint8_t)Byte::OptionsByte],
						IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
						IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
						font,
						(char*)&cue[(uint8_t)Byte::OptionsByte + 7],
						cue[(uint8_t)Byte::OptionsByte + 6]
					);

					delete font;
				}
				break;
			case Action::DrawTriangle:
				canvas->draw_triangle(
					cue[(uint8_t)Byte::OptionsByte],
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 9]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 11]),
					(bool)cue[(uint8_t)Byte::OptionsByte + 13]);
				break;
			case Action::ErasePoint:
				canvas->erase_point(
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2])
				);
				break;
			case Action::NextFrame:
				canvas->next_frame();
				break;
			case Action::PreviousFrame:
				canvas->previous_frame();
				break;
			case Action::RemoveFrameTimer:
				canvas->remove_frame_timer();
				break;
			case Action::SetCurrentFrameIndex:
				canvas->set_current_frame_index(IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetFrameTimer:
				canvas->set_frame_timer(IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetNumFrames:
				canvas->set_num_frames(IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetPalette:
				{
					uint8_t num_colors = cue[(uint8_t)Byte::OptionsByte];

					// Delete the old Palette after setting the new one.
					Palette* old_palette = canvas->get_palette();
					canvas->set_palette(deserialize_palette(&cue[(uint8_t)Byte::OptionsByte + 1], num_colors));
					delete old_palette;
				}
				break;
			case Action::StartFrameTimer:
				if (canvas->get_frame_timer()) {
					canvas->get_frame_timer()->start();
				}
				break;
			case Action::StopFrameTimer:
				if (canvas->get_frame_timer()) {
					canvas->get_frame_timer()->stop();
				}
				break;
			default:
				break;
		}
	}

	CanvasCueHandler::~CanvasCueHandler() { }
}
