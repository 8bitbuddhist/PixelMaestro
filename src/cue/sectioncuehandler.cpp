#include "animationcuehandler.h"
#include "cuecontroller.h"
#include "sectioncuehandler.h"

namespace PixelMaestro {
	void SectionCueHandler::add_canvas(unsigned char section_num, unsigned char overlay_num, CanvasType::Type canvas_type) {
		controller_->get_cue()[Byte::HandlerByte] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (unsigned char)Action::AddCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = canvas_type;

		controller_->assemble((unsigned char)Byte::OptionsByte);
	}

	void SectionCueHandler::add_overlay(unsigned char section_num, unsigned char overlay_num, Colors::MixMode mix_mode, unsigned char alpha) {
		controller_->get_cue()[Byte::HandlerByte] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (unsigned char)Action::AddOverlay;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = mix_mode;
		controller_->get_cue()[Byte::OptionsByte + 1] = alpha;

		controller_->assemble((unsigned char)Byte::OptionsByte + 2);
	}

	void SectionCueHandler::set_animation(unsigned char section_num, unsigned char overlay_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors) {

		controller_->get_cue()[Byte::HandlerByte] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (unsigned char)Action::SetAnimation;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = (unsigned char)animation_type;
		controller_->get_cue()[Byte::OptionsByte + 1] = (unsigned char)preserve_cycle_index;
		controller_->get_cue()[Byte::OptionsByte + 2] = num_colors;

		unsigned char colors_index = Byte::OptionsByte + 3;
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

	void SectionCueHandler::set_dimensions(unsigned char section_num, unsigned char overlay_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		controller_->get_cue()[Byte::HandlerByte] = (unsigned char)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (unsigned char)Action::SetDimensions;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = y_byte.converted_1;

		controller_->assemble((unsigned char)Byte::OptionsByte + 4);
	}

	void SectionCueHandler::run(unsigned char *cue) {
		Section* section = controller_->get_maestro()->get_section(cue[Byte::SectionByte]);

		for (unsigned char i = 0; i < cue[Byte::OverlayByte]; i++) {
			section = section->get_overlay()->section;
		}

		switch ((Action)cue[Byte::ActionByte]) {
			case Action::AddCanvas:
				section->add_canvas(CanvasType::Type(cue[Byte::OptionsByte]));
				break;
			case Action::AddOverlay:
				section->add_overlay(Colors::MixMode(cue[Byte::OptionsByte]), cue[Byte::OptionsByte + 1]);
				break;
			case Action::SetAnimation:
				{
					unsigned char num_colors = cue[Byte::OptionsByte + 2];
					if (num_colors == 0) {
						return;
					}
					unsigned char colors_index = Byte::OptionsByte + 3;
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
						section->set_animation(animation, (bool)cue[Byte::OptionsByte + 1]);
						animation->set_colors(colors, num_colors);
					}
				}
				break;
			case Action::SetDimensions:
				{
					unsigned short x = IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]);
					unsigned short y = IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]);
					section->set_dimensions(x, y);
				}
				break;
		}
	}

	SectionCueHandler::~SectionCueHandler() { }
}
