#include "animationcuehandler.h"
#include "cuecontroller.h"
#include "sectioncuehandler.h"

namespace PixelMaestro {
	void SectionCueHandler::add_canvas(unsigned char section_num, CanvasType::Type canvas_type) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::AddCanvas;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = canvas_type;

		controller_->assemble((unsigned char)Bit::OptionsBit);
	}

	void SectionCueHandler::add_overlay(unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::AddOverlay;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = mix_mode;
		controller_->get_cue()[Bit::OptionsBit + 1] = alpha;

		controller_->assemble((unsigned char)Bit::OptionsBit + 2);
	}

	void SectionCueHandler::set_animation(unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors) {

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetAnimation;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = (unsigned char)animation_type;
		controller_->get_cue()[Bit::OptionsBit + 1] = (unsigned char)preserve_cycle_index;
		controller_->get_cue()[Bit::OptionsBit + 2] = num_colors;

		unsigned char colors_index = Bit::OptionsBit + 3;
		for (unsigned char i = 0; i < num_colors; i++) {
			controller_->get_cue()[colors_index] = colors[i].r;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].g;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].b;
			colors_index++;
		}

		controller_->assemble(colors_index);
	}

	void SectionCueHandler::set_dimensions(unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetDimensions;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = x_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = x_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = y_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = y_byte.converted_1;

		controller_->assemble((unsigned char)Bit::OptionsBit + 4);
	}

	void SectionCueHandler::run(unsigned char *cue) {
		Section* section = controller_->get_maestro()->get_section(cue[Bit::SectionBit]);
		switch ((Action)cue[Bit::ActionBit]) {
			case Action::AddCanvas:
				section->add_canvas(CanvasType::Type(cue[Bit::OptionsBit]));
				break;
			case Action::AddOverlay:
				section->add_overlay(Colors::MixMode(cue[Bit::OptionsBit]), cue[Bit::OptionsBit + 1]);
				break;
			case Action::SetAnimation:
				{
					unsigned char num_colors = cue[Bit::OptionsBit + 2];
					if (num_colors == 0) {
						return;
					}
					unsigned char colors_index = Bit::OptionsBit + 3;
					Colors::RGB colors[num_colors];
					for (unsigned char i = 0; i < num_colors; i++) {
						colors[i].r = cue[colors_index];
						colors_index++;
						colors[i].g = cue[colors_index];
						colors_index++;
						colors[i].b = cue[colors_index];
						colors_index++;
					}
					Animation* animation = AnimationCueHandler::initialize_animation(cue);
					if (animation != nullptr) {
						/*
						 * Potential memory leak with this and AnimationCue::initialize.
						 * Delete the Section's existing Animation before assigning a new one.
						 */
						delete section->get_animation();
						section->set_animation(animation, (bool)cue[Bit::OptionsBit + 1]);
						animation->set_colors(colors, num_colors);
					}
				}
				break;
			case Action::SetDimensions:
				{
					unsigned short x = IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]);
					unsigned short y = IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]);
					section->set_dimensions(x, y);
				}
				break;
		}
	}
}
