#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "../canvas/palettecanvas.h"
#include "../canvas/fonts/font5x8.h"
#include "canvascuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {

	uint8_t* CanvasCueHandler::activate(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::Activate;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	uint8_t* CanvasCueHandler::clear(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::Clear;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::deactivate(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::Deactivate;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	uint8_t* CanvasCueHandler::draw_circle(uint8_t section_num, uint8_t layer_num, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawCircle;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = radius_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = radius_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 7);
	}

	uint8_t* CanvasCueHandler::draw_circle(uint8_t section_num, uint8_t layer_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawCircle;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color.r;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = color.g;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = color.b;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = radius_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = radius_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 9] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 10);
	}

	uint8_t* CanvasCueHandler::draw_circle(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawCircle;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
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

	uint8_t* CanvasCueHandler::draw_frame(uint8_t section_num, uint8_t layer_num, uint16_t size_x, uint16_t size_y, bool *frame) {
		// Check the size of the buffer. If it's not big enough to store the frame, exit.
		if ((size_x * size_y) > controller_->get_buffer_size()) {
			return nullptr;
		}

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawFrame;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = size_x;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = size_y;

		uint16_t current_index = (uint8_t)Byte::OptionsByte + 2;
		Point grid(size_x, size_y);
		for (uint16_t y = 0; y < size_y; y++) {
			for (uint16_t x = 0; x < size_x; x++) {
				controller_->get_buffer()[current_index] = (uint8_t)frame[grid.get_inline_index(x, y)];
				current_index++;
			}
		}

		return controller_->assemble(current_index);
	}

	uint8_t* CanvasCueHandler::draw_frame(uint8_t section_num, uint8_t layer_num, uint16_t size_x, uint16_t size_y, Colors::RGB* frame) {
		// Check the size of the buffer. If it's not big enough to store the frame, exit.
		if ((size_x * size_y) * 3 > controller_->get_buffer_size()) {
			return nullptr;
		}

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawFrame;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = size_x;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = size_y;

		uint16_t current_index = (uint8_t)Byte::OptionsByte + 2;
		Point grid(size_x, size_y);
		for (uint16_t y = 0; y < size_y; y++) {
			for (uint16_t x = 0; x < size_x; x++) {
				controller_->get_buffer()[current_index] = frame[grid.get_inline_index(x, y)].r;
				current_index++;
				controller_->get_buffer()[current_index] = frame[grid.get_inline_index(x, y)].g;
				current_index++;
				controller_->get_buffer()[current_index] = frame[grid.get_inline_index(x, y)].b;
				current_index++;
			}
		}

		return controller_->assemble(current_index);
	}

	uint8_t* CanvasCueHandler::draw_frame(uint8_t section_num, uint8_t layer_num, uint16_t size_x, uint16_t size_y, uint8_t* frame) {
		// Check the size of the buffer. If it's not big enough to store the frame, exit.
		if ((size_x * size_y) > controller_->get_buffer_size()) {
			return nullptr;
		}

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawFrame;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
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

	uint8_t* CanvasCueHandler::draw_line(uint8_t section_num, uint8_t layer_num, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawLine;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = target_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = target_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = target_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = target_y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 8);
	}

	uint8_t* CanvasCueHandler::draw_line(uint8_t section_num, uint8_t layer_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawLine;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color.r;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = color.g;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = color.b;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = target_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = target_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 9] = target_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 10] = target_y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 11);
	}

	uint8_t* CanvasCueHandler::draw_line(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawLine;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
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

	uint8_t* CanvasCueHandler::draw_point(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawPoint;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	uint8_t* CanvasCueHandler::draw_point(uint8_t section_num, uint8_t layer_num, Colors::RGB color, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawPoint;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color.r;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = color.g;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = color.b;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 7);
	}

	uint8_t* CanvasCueHandler::draw_point(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t x, uint16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawPoint;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 5);
	}

	uint8_t* CanvasCueHandler::draw_rect(uint8_t section_num, uint8_t layer_num, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawRect;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = size_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = size_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = size_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = size_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 9);
	}

	uint8_t* CanvasCueHandler::draw_rect(uint8_t section_num, uint8_t layer_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawRect;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color.r;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = color.g;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = color.b;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = size_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = size_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 9] = size_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 10] = size_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 11] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 12);
	}

	uint8_t* CanvasCueHandler::draw_rect(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawRect;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
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

	uint8_t* CanvasCueHandler::draw_triangle(uint8_t section_num, uint8_t layer_num, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawTriangle;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = point_a_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = point_a_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = point_a_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = point_a_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = point_b_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = point_b_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = point_b_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = point_b_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = point_c_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 9] = point_c_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 10] = point_c_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 11] = point_c_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 12] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 13);
	}

	uint8_t* CanvasCueHandler::draw_triangle(uint8_t section_num, uint8_t layer_num, Colors::RGB color, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawTriangle;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color.r;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = color.g;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = color.b;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = point_a_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = point_a_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = point_a_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = point_a_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = point_b_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = point_b_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 9] = point_b_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 10] = point_b_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 11] = point_c_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 12] = point_c_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 13] = point_c_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 14] = point_c_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 15] = (uint8_t)fill;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 16);
	}

	uint8_t* CanvasCueHandler::draw_triangle(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawTriangle;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
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

	uint8_t* CanvasCueHandler::draw_text(uint8_t section_num, uint8_t layer_num, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawText;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::AnimationCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = (uint8_t)font;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = num_chars;

		uint8_t text_index = (uint8_t)Byte::OptionsByte + 6;
		for (uint8_t i = 0; i < num_chars; i++) {
			controller_->get_buffer()[text_index] = text[i];
			text_index++;
		}

		return controller_->assemble(text_index);
	}

	uint8_t* CanvasCueHandler::draw_text(uint8_t section_num, uint8_t layer_num, Colors::RGB color, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawText;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color.r;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = color.g;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = color.b;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = origin_x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = origin_x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = origin_y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = origin_y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = (uint8_t)font;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 8] = num_chars;

		uint8_t text_index = (uint8_t)Byte::OptionsByte + 9;
		for (uint8_t i = 0; i < num_chars; i++) {
			controller_->get_buffer()[text_index] = text[i];
			text_index++;
		}

		return controller_->assemble(text_index);
	}

	uint8_t* CanvasCueHandler::draw_text(uint8_t section_num, uint8_t layer_num, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, Font::Type font, const char* text, uint8_t num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::DrawText;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
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

	uint8_t* CanvasCueHandler::next_frame(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::NextFrame;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::previous_frame(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::PreviousFrame;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::remove_frame_timer(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::RemoveFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::set_colors(uint8_t section_num, uint8_t layer_num, Colors::RGB *colors, uint8_t num_colors) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetColors;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = num_colors;

		uint16_t colors_index = (uint8_t)Byte::OptionsByte + 1;
		for (uint8_t i = 0; i < num_colors; i++) {
			controller_->get_buffer()[colors_index] = colors[i].r;
			colors_index++;
			controller_->get_buffer()[colors_index] = colors[i].g;
			colors_index++;
			controller_->get_buffer()[colors_index] = colors[i].b;
			colors_index++;
		}

		return controller_->assemble(colors_index);
	}

	uint8_t* CanvasCueHandler::set_current_frame_index(uint8_t section_num, uint8_t layer_num, uint16_t index) {
		IntByteConvert index_byte(index);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetCurrentFrameIndex;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = index_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = index_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* CanvasCueHandler::set_drawing_color(uint8_t section_num, uint8_t layer_num, Colors::RGB color) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetDrawingColor;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::ColorCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color.r;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = color.g;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = color.b;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 3);
	}

	uint8_t* CanvasCueHandler::set_drawing_color(uint8_t section_num, uint8_t layer_num, uint8_t color_index) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetDrawingColor;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = (uint8_t)CanvasType::PaletteCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = color_index;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 1);
	}

	uint8_t* CanvasCueHandler::set_frame_timer(uint8_t section_num, uint8_t layer_num, uint16_t speed) {
		IntByteConvert speed_byte(speed);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = speed_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = speed_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* CanvasCueHandler::set_num_frames(uint8_t section_num, uint8_t layer_num, uint16_t num_frames) {
		IntByteConvert num_frames_byte(num_frames);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetNumFrames;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = num_frames_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = num_frames_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* CanvasCueHandler::start_frame_timer(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::StartFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* CanvasCueHandler::stop_frame_timer(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::CanvasHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::StopFrameTimer;
		controller_->get_buffer()[(uint8_t)Byte::TypeByte] = 255;
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

		if (section == nullptr)
			return;

		// Check generic actions
		Canvas* plain_canvas = section->get_canvas();
		if (plain_canvas == nullptr) return;
		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::Activate:
				plain_canvas->activate(
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2])
				);
				break;
			case Action::Clear:
				plain_canvas->clear();
				break;
			case Action::Deactivate:
				plain_canvas->deactivate(
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2])
				);
				break;
			case Action::NextFrame:
				plain_canvas->next_frame();
				break;
			case Action::PreviousFrame:
				plain_canvas->previous_frame();
				break;
			case Action::RemoveFrameTimer:
				plain_canvas->remove_frame_timer();
				break;
			case Action::SetCurrentFrameIndex:
				plain_canvas->set_current_frame_index(IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetFrameTimer:
				plain_canvas->set_frame_timer(IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::SetNumFrames:
				plain_canvas->set_num_frames(IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::StartFrameTimer:
				if (plain_canvas->get_frame_timer()) {
					plain_canvas->get_frame_timer()->start();
				}
				break;
			case Action::StopFrameTimer:
				if (plain_canvas->get_frame_timer()) {
					plain_canvas->get_frame_timer()->stop();
				}
				break;
			default:
				break;
		}

		// Check Canvas-specific actions
		switch ((CanvasType)cue[(uint8_t)Byte::TypeByte]) {
			case CanvasType::AnimationCanvas:
				{
					AnimationCanvas* animation_canvas = static_cast<AnimationCanvas*>(plain_canvas);
					switch((Action)cue[(uint8_t)Byte::ActionByte]) {
						case Action::DrawCircle:
							animation_canvas->draw_circle(
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 4]),
								(bool)cue[(uint8_t)Byte::OptionsByte + 6]);
							break;
						case Action::DrawFrame:
							{
								Point frame_bounds(cue[(uint8_t)Byte::OptionsByte], cue[(uint8_t)Byte::OptionsByte + 1]);
								for (uint16_t y = 0; y < frame_bounds.y; y++) {
									for (uint16_t x = 0; x < frame_bounds.x; x++) {
										if (cue[(uint8_t)Byte::OptionsByte + 2 + frame_bounds.get_inline_index(x, y)] == 1) {
											animation_canvas->draw_point(x, y);
										}
									}
								}
							}
							break;
						case Action::DrawLine:
							animation_canvas->draw_line(
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 4]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 6]));
							break;
						case Action::DrawPoint:
							animation_canvas->draw_point(
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]));
							break;
						case Action::DrawRect:
							animation_canvas->draw_rect(
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 4]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 6]),
								(bool)cue[(uint8_t)Byte::OptionsByte + 8]);
							break;
						case Action::DrawText:
							{
								Font* font = get_font((Font::Type)cue[(uint8_t)Byte::OptionsByte + 4]);

								animation_canvas->draw_text(
									IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
									IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]),
									font,
									(char*)&cue[(uint8_t)Byte::OptionsByte + 6],
									cue[(uint8_t)Byte::OptionsByte + 5]
								);

								delete font;
							}
							break;
						case Action::DrawTriangle:
							animation_canvas->draw_triangle(
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 4]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 6]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 8]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 10]),
								(bool)cue[(uint8_t)Byte::OptionsByte + 12]);
							break;
						default:
							break;
					}
				}
				break;
			case CanvasType::ColorCanvas:
				{
					ColorCanvas* color_canvas = static_cast<ColorCanvas*>(plain_canvas);
					Colors::RGB color = {
						cue[(uint8_t)Byte::OptionsByte],
						cue[(uint8_t)Byte::OptionsByte + 1],
						cue[(uint8_t)Byte::OptionsByte + 2]
					};
					switch((Action)cue[(uint8_t)Byte::ActionByte]) {
						case Action::DrawCircle:
							color_canvas->draw_circle(
								color,
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]),
								bool(cue[(uint8_t)Byte::OptionsByte + 9]));
							break;
						case Action::DrawFrame:
							{
								uint32_t current_index = (uint8_t)Byte::OptionsByte + 2;
								Point frame_bounds(cue[(uint8_t)Byte::OptionsByte], cue[(uint8_t)Byte::OptionsByte + 1]);
								for (uint16_t y = 0; y < frame_bounds.y; y++) {
									for (uint16_t x = 0; x < frame_bounds.x; x++) {
										Colors::RGB color(cue[current_index],
												cue[current_index + 1],
												cue[current_index + 2]);

										color_canvas->draw_point(color, x, y);
										current_index += 3;
									}
								}
							}
							break;
						case Action::DrawLine:
							color_canvas->draw_line(
								color,
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 9]));
							break;
						case Action::DrawPoint:
							color_canvas->draw_point(
								color,
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]));
							break;
						case Action::DrawRect:
							color_canvas->draw_rect(
								color,
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 9]),
								bool(cue[(uint8_t)Byte::OptionsByte + 11]));
							break;
						case Action::DrawText:
							{
								Font* font = get_font((Font::Type)cue[(uint8_t)Byte::OptionsByte + 7]);

								Colors::RGB color = {
									cue[(uint8_t)Byte::OptionsByte],
									cue[(uint8_t)Byte::OptionsByte + 1],
									cue[(uint8_t)Byte::OptionsByte + 2]
								};

								color_canvas->draw_text(
									color,
									IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
									IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
									font,
									(char*)&cue[(uint8_t)Byte::OptionsByte + 9],
									cue[(uint8_t)Byte::OptionsByte + 8]
								);

								delete font;
							}
							break;
						case Action::DrawTriangle:
							color_canvas->draw_triangle(
								color,
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 9]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 11]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 13]),
								bool(cue[(uint8_t)Byte::OptionsByte + 15]));
							break;
						case Action::SetDrawingColor:
							color_canvas->set_drawing_color(
								Colors::RGB(
									cue[(uint8_t)Byte::OptionsByte],
									cue[(uint8_t)Byte::OptionsByte + 1],
									cue[(uint8_t)Byte::OptionsByte + 2]
								)
							);
							break;
						default:
							break;
					}
				}
				break;
			case CanvasType::PaletteCanvas:
				{
					PaletteCanvas* palette_canvas = static_cast<PaletteCanvas*>(plain_canvas);
					switch((Action)cue[(uint8_t)Byte::ActionByte]) {
						case Action::DrawCircle:
							palette_canvas->draw_circle(
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
										palette_canvas->draw_point(cue[(uint8_t)Byte::OptionsByte + 2 + frame_bounds.get_inline_index(x, y)], x, y);
									}
								}
							}
							break;
						case Action::DrawLine:
							palette_canvas->draw_line(
								cue[(uint8_t)Byte::OptionsByte],
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]));
							break;
						case Action::DrawPoint:
							palette_canvas->draw_point(
								cue[(uint8_t)Byte::OptionsByte],
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]));
							break;
						case Action::DrawRect:
							palette_canvas->draw_rect(
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

								palette_canvas->draw_text(
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
							palette_canvas->draw_triangle(
								cue[(uint8_t)Byte::OptionsByte],
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 1]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 3]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 5]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 7]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 9]),
								IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 11]),
								(bool)cue[(uint8_t)Byte::OptionsByte + 13]);
							break;
						case Action::SetColors:
							{
								uint8_t num_colors = cue[(uint8_t)Byte::OptionsByte];
								uint16_t current_color_index = 1;
								Colors::RGB* colors = new Colors::RGB[num_colors];
								for (uint8_t i = 0; i < num_colors; i++) {
									colors[i].r = cue[(uint8_t)Byte::OptionsByte + current_color_index];
									current_color_index++;
									colors[i].g = cue[(uint8_t)Byte::OptionsByte + current_color_index];
									current_color_index++;
									colors[i].b = cue[(uint8_t)Byte::OptionsByte + current_color_index];
									current_color_index++;
								}

								//Delete the old palette after setting the new one.
								Colors::RGB* old_palette_colors = palette_canvas->get_palette()->get_colors();

								palette_canvas->set_palette(colors, num_colors);

								delete [] old_palette_colors;
							}
							break;
						case Action::SetDrawingColor:
							palette_canvas->set_drawing_color(cue[(uint8_t)Byte::OptionsByte]);
							break;
						default:
							break;
					}
				}
				break;
		}
	}

	CanvasCueHandler::~CanvasCueHandler() { }
}
