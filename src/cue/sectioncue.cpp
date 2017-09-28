#include "animationcue.h"
#include "cue.h"
#include "sectioncue.h"

/*
 *  FIXME: Lots of work.
 *		This is failing because the Bit enums are pointing to two different memory locations: one buffer-based and one payload-based.
 *		Reconfigure all actions to write directly to buffer and undo this whole buffer vs. payload mess.
 *		This might make it easier to find a way to allocate the buffer in advance somehow.
 */
namespace PixelMaestro {
	void SectionCue::add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type) {
		unsigned char size = (unsigned char)Bit::OptionsBit;
		unsigned char payload[size];
		payload[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		payload[Bit::ActionBit] = (unsigned char)Action::AddCanvas;
		payload[Bit::SectionBit] = section_num;
		payload[Bit::OptionsBit] = canvas_type;

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha) {

		unsigned char size = (unsigned char)Bit::OptionsBit + 2;
		unsigned char payload[size];
		payload[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		payload[Bit::ActionBit] = (unsigned char)Action::AddOverlay;
		payload[Bit::SectionBit] = section_num;
		payload[Bit::OptionsBit] = mix_mode;
		payload[Bit::OptionsBit + 1] = alpha;

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::set_animation(unsigned char *buffer, unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors) {

		unsigned char colors_index = Bit::OptionsBit + 3;
		unsigned char payload[colors_index + (num_colors * 3)];
		payload[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		payload[Bit::ActionBit] = (unsigned char)Action::SetAnimation;
		payload[Bit::SectionBit] = section_num;
		payload[Bit::OptionsBit] = (unsigned char)animation_type;
		payload[Bit::OptionsBit + 1] = (unsigned char)preserve_cycle_index;
		payload[Bit::OptionsBit + 2] = num_colors;

		for (unsigned char i = 0; i < num_colors; i++) {
			payload[colors_index] = colors[i].r;
			colors_index++;
			payload[colors_index] = colors[i].g;
			colors_index++;
			payload[colors_index] = colors[i].b;
			colors_index++;
		}

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::set_dimensions(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);
		unsigned char size = (unsigned char)Bit::OptionsBit + 4;
		unsigned char payload[size];
		payload[Bit::ComponentBit] = (unsigned char)Cue::Component::Section;
		payload[Bit::ActionBit] = (unsigned char)Action::SetDimensions;
		payload[Bit::SectionBit] = (unsigned char)Action::SetDimensions;
		payload[Bit::OptionsBit] = x_byte.converted_0;
		payload[Bit::OptionsBit + 1] = x_byte.converted_1;
		payload[Bit::OptionsBit + 2] = y_byte.converted_0;
		payload[Bit::OptionsBit + 3] = y_byte.converted_1;

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::run(Maestro *maestro, unsigned char *cue) {
		Section* section = maestro->get_section(cue[SectionCue::Bit::SectionBit]);
		switch ((Action)cue[SectionCue::Bit::ActionBit]) {
			case Action::AddCanvas:
				section->add_canvas(CanvasType::Type(cue[SectionCue::Bit::OptionsBit]));
				break;
			case Action::AddOverlay:
				section->add_overlay(Colors::MixMode(cue[SectionCue::Bit::OptionsBit]), cue[SectionCue::Bit::OptionsBit + 1]);
				break;
			case Action::SetAnimation:
				{
					unsigned char num_colors = cue[SectionCue::Bit::OptionsBit + 2];
					if (num_colors == 0) {
						return;
					}
					unsigned char colors_index = SectionCue::Bit::OptionsBit + 3;
					Colors::RGB colors[num_colors];
					for (unsigned char i = 0; i < num_colors; i++) {
						colors[i].r = cue[colors_index];
						colors_index++;
						colors[i].g = cue[colors_index];
						colors_index++;
						colors[i].b = cue[colors_index];
						colors_index++;
					}
					Animation* animation = section->set_animation(AnimationCue::initialize_animation(cue), (bool)cue[SectionCue::Bit::OptionsBit + 1]);
					animation->set_colors(colors, num_colors);
				}
				break;
			case Action::SetDimensions:
				section->set_dimensions(
					IntByteConvert::byte_to_int(&cue[SectionCue::Bit::OptionsBit]),
					IntByteConvert::byte_to_int(&cue[SectionCue::Bit::OptionsBit + 2]));
				break;
		}
	}
}
