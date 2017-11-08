#include "cuecontroller.h"
#include "sectioncuehandler.h"

namespace PixelMaestro {
	void SectionCueHandler::remove_canvas(uint8_t section_num, uint8_t overlay_num) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::RemoveCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;

		controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	void SectionCueHandler::set_animation(uint8_t section_num, uint8_t overlay_num, AnimationType::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, uint8_t num_colors, bool delete_old_colors) {

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetAnimation;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = (uint8_t)animation_type;
		controller_->get_cue()[Byte::OptionsByte + 1] = (uint8_t)preserve_cycle_index;
		controller_->get_cue()[Byte::OptionsByte + 2] = num_colors;

		uint8_t colors_index = Byte::OptionsByte + 3;
		for (uint8_t i = 0; i < num_colors; i++) {
			controller_->get_cue()[colors_index] = colors[i].r;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].g;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].b;
			colors_index++;
		}

		controller_->get_cue()[colors_index] = delete_old_colors;

		controller_->assemble(colors_index);
	}

	void SectionCueHandler::set_canvas(uint8_t section_num, uint8_t overlay_num, CanvasType::Type canvas_type, uint16_t num_frames) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = canvas_type;
		controller_->get_cue()[Byte::OptionsByte + 1] = num_frames;

		controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	void SectionCueHandler::set_dimensions(uint8_t section_num, uint8_t overlay_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetDimensions;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = y_byte.converted_1;

		controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	void SectionCueHandler::set_overlay(uint8_t section_num, uint8_t overlay_num, Colors::MixMode mix_mode, uint8_t alpha) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetOverlay;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = (uint8_t)mix_mode;
		controller_->get_cue()[Byte::OptionsByte + 1] = alpha;

		controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	void SectionCueHandler::run(uint8_t *cue) {
		Section* section = get_section(cue[Byte::SectionByte], cue[Byte::OverlayByte]);

		if (section == nullptr) return;

		switch ((Action)cue[Byte::ActionByte]) {
			case Action::RemoveCanvas:
				section->remove_canvas();
				break;
			case Action::SetAnimation:
				{
					uint8_t num_colors = cue[Byte::OptionsByte + 2];
					uint8_t colors_index = Byte::OptionsByte + 3;
					Colors::RGB* colors = nullptr;

					if (num_colors > 0) {
						colors = new Colors::RGB[num_colors];
						for (uint8_t i = 0; i < num_colors; i++) {
							colors[i].r = cue[colors_index];
							colors_index++;
							colors[i].g = cue[colors_index];
							colors_index++;
							colors[i].b = cue[colors_index];
							colors_index++;
						}
					}

					// Delete any previous animation colors to prevent memory leaks.
					if (cue[colors_index] && section->get_animation() != nullptr) {
						delete[] section->get_animation()->get_colors();
					}

					section->set_animation((AnimationType::Type)cue[SectionCueHandler::Byte::OptionsByte], colors, num_colors, (bool)cue[Byte::OptionsByte + 1]);
				}
				break;
			case Action::SetCanvas:
				section->set_canvas(CanvasType::Type(cue[Byte::OptionsByte]), cue[Byte::OptionsByte + 1]);
				break;
			case Action::SetDimensions:
				section->set_dimensions(
					IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]));
				break;
			case Action::SetOverlay:
				section->set_overlay(Colors::MixMode(cue[Byte::OptionsByte]), cue[Byte::OptionsByte + 1]);
				break;
			default:
				break;
		}
	}

	SectionCueHandler::~SectionCueHandler() { }
}
