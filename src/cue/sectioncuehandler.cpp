#include "cuecontroller.h"
#include "sectioncuehandler.h"

namespace PixelMaestro {
	uint8_t* SectionCueHandler::remove_animation(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::RemoveAnimation;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* SectionCueHandler::remove_canvas(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::RemoveCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* SectionCueHandler::remove_layer(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::RemoveLayer;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* SectionCueHandler::set_animation(uint8_t section_num, uint8_t layer_num, AnimationType animation_type, bool preserve_settings) {

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetAnimation;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)animation_type;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = (uint8_t)preserve_settings;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* SectionCueHandler::set_canvas(uint8_t section_num, uint8_t layer_num, CanvasType canvas_type, uint16_t num_frames) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetCanvas;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)canvas_type;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = num_frames;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* SectionCueHandler::set_dimensions(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetDimensions;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	uint8_t* SectionCueHandler::set_layer(uint8_t section_num, uint8_t layer_num, Colors::MixMode mix_mode, uint8_t alpha) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetLayer;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)mix_mode;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = alpha;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	uint8_t* SectionCueHandler::set_offset(uint8_t section_num, uint8_t layer_num, int16_t x, int16_t y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetOffset;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_1;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	uint8_t* SectionCueHandler::set_scroll(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y, bool reverse_x, bool reverse_y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetScroll;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = y_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = (uint8_t)reverse_x;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = (uint8_t)reverse_y;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 6);
	}

	void SectionCueHandler::run(uint8_t *cue) {
		Section* section = get_section(cue[(uint8_t)Byte::SectionByte], cue[(uint8_t)Byte::LayerByte]);

		if (section == nullptr) return;

		switch ((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::RemoveAnimation:
				section->remove_animation();
				break;
			case Action::RemoveCanvas:
				section->remove_canvas();
				break;
			case Action::RemoveLayer:
				section->remove_layer();
				break;
			case Action::SetAnimation:
				section->set_animation((AnimationType)cue[(uint8_t)Byte::OptionsByte],
						(bool)cue[(uint8_t)Byte::OptionsByte + 1]);
				break;
			case Action::SetCanvas:
				section->set_canvas(CanvasType(cue[(uint8_t)Byte::OptionsByte]), cue[(uint8_t)Byte::OptionsByte + 1]);
				break;
			case Action::SetDimensions:
				section->set_dimensions(
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]));
				break;
			case Action::SetLayer:
				section->set_layer(Colors::MixMode(cue[(uint8_t)Byte::OptionsByte]), cue[(uint8_t)Byte::OptionsByte + 1]);
				break;
			case Action::SetOffset:
				section->set_offset(
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2])
				);
				break;
			case Action::SetScroll:
				section->set_scroll(
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]),
					(bool)cue[(uint8_t)Byte::OptionsByte + 4],
					(bool)cue[(uint8_t)Byte::OptionsByte + 5]
				);
				break;
			default:
				break;
		}
	}

	SectionCueHandler::~SectionCueHandler() { }
}
