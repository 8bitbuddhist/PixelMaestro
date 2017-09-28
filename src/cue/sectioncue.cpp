#include "animationcue.h"
#include "cue.h"
#include "sectioncue.h"

namespace PixelMaestro {
	void SectionCue::add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type) {
		buffer[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		buffer[Bit::ActionBit] = (unsigned char)Action::AddCanvas;
		buffer[Bit::SectionBit] = section_num;
		buffer[Bit::OptionsBit] = canvas_type;

		Cue::assemble(buffer, (unsigned char)Bit::OptionsBit);
	}

	void SectionCue::add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha) {
		buffer[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		buffer[Bit::ActionBit] = (unsigned char)Action::AddOverlay;
		buffer[Bit::SectionBit] = section_num;
		buffer[Bit::OptionsBit] = mix_mode;
		buffer[Bit::OptionsBit + 1] = alpha;

		Cue::assemble(buffer, (unsigned char)Bit::OptionsBit + 2);
	}

	void SectionCue::set_animation(unsigned char *buffer, unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors) {

		buffer[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		buffer[Bit::ActionBit] = (unsigned char)Action::SetAnimation;
		buffer[Bit::SectionBit] = section_num;
		buffer[Bit::OptionsBit] = (unsigned char)animation_type;
		buffer[Bit::OptionsBit + 1] = (unsigned char)preserve_cycle_index;
		buffer[Bit::OptionsBit + 2] = num_colors;

		unsigned char colors_index = Bit::OptionsBit + 3;
		for (unsigned char i = 0; i < num_colors; i++) {
			buffer[colors_index] = colors[i].r;
			colors_index++;
			buffer[colors_index] = colors[i].g;
			colors_index++;
			buffer[colors_index] = colors[i].b;
			colors_index++;
		}

		Cue::assemble(buffer, colors_index);
	}

	void SectionCue::set_dimensions(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		buffer[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		buffer[Bit::ActionBit] = (unsigned char)Action::SetDimensions;
		buffer[Bit::SectionBit] = section_num;
		buffer[Bit::OptionsBit] = x_byte.converted_0;
		buffer[Bit::OptionsBit + 1] = x_byte.converted_1;
		buffer[Bit::OptionsBit + 2] = y_byte.converted_0;
		buffer[Bit::OptionsBit + 3] = y_byte.converted_1;

		Cue::assemble(buffer, (unsigned char)Bit::OptionsBit + 4);
	}

	void SectionCue::run(Maestro *maestro, unsigned char *cue) {
		Section* section = maestro->get_section(cue[Bit::SectionBit]);
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
					Animation* animation = section->set_animation(AnimationCue::initialize_animation(cue), (bool)cue[Bit::OptionsBit + 1]);
					animation->set_colors(colors, num_colors);
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
