#include "animationcue.h"
#include "cue.h"
#include "sectioncue.h"

namespace PixelMaestro {
	void SectionCue::add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Section,
			(unsigned char)Action::AddCanvas,
			section_num,
			canvas_type
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Section,
			(unsigned char)Action::AddOverlay,
			section_num,
			mix_mode,
			alpha
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::set_animation(unsigned char *buffer, unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors) {

		unsigned char payload[3 + (num_colors * 3)];
		payload[0] = (unsigned char)Cue::Component::Section;
		payload[1] = (unsigned char)Action::SetAnimation;
		payload[2] = section_num;
		payload[3] = (unsigned char)animation_type;
		payload[4] = (unsigned char)preserve_cycle_index;

		int colors_index = 5;
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
		unsigned char payload[] {
			(unsigned char)Cue::Component::Section,
			(unsigned char)Action::SetDimensions,
			section_num,
			x_byte.converted_0,
			x_byte.converted_1,
			y_byte.converted_0,
			y_byte.converted_1
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::run(Maestro *maestro, unsigned char *cue) {
		Section* section = maestro->get_section(cue[Cue::payload_index_ + 2]);
		switch ((Action)cue[Cue::payload_index_ + 1]) {
			case Action::AddCanvas:
				section->add_canvas(CanvasType::Type(cue[Cue::payload_index_ + 3]));
				break;
			case Action::AddOverlay:
				section->add_overlay(Colors::MixMode(cue[Cue::payload_index_ + 3]), cue[Cue::payload_index_ + 4]);
				break;
			case Action::SetAnimation:
				section->set_animation(AnimationCue::initialize_animation(cue), (bool)cue[Cue::payload_index_ + 4]);
				break;
			case Action::SetDimensions:
				section->set_dimensions(
					IntByteConvert::byte_to_int(&cue[Cue::payload_index_ + 3]),
					IntByteConvert::byte_to_int(&cue[Cue::payload_index_ + 5]));
				break;
		}
	}
}
