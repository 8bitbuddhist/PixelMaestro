#include "animationcue.h"
#include "cue.h"

namespace PixelMaestro {
	void AnimationCue::set_colors(unsigned char *buffer, unsigned char section_num, Colors::RGB *colors, unsigned char num_colors) {
		int colors_index = 4;

		unsigned char payload[colors_index + (num_colors * 3)];
		payload[0] = (unsigned char)Cue::Component::Animation;
		payload[1] = (unsigned char)Action::SetColors;
		payload[2] = section_num;
		payload[3] = num_colors;

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

	void AnimationCue::set_cycle_index(unsigned char *buffer, unsigned char section_num, unsigned char cycle_index) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetCycleIndex,
			section_num,
			cycle_index
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_fade(unsigned char* buffer, unsigned char section_num, bool fade) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetFade,
			section_num,
			(unsigned char)fade
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_orientation(unsigned char *buffer, unsigned char section_num, Animation::Orientation orientation) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetReverse,
			section_num,
			(unsigned char)orientation
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_reverse(unsigned char *buffer, unsigned char section_num, bool reverse) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetReverse,
			section_num,
			(unsigned char)reverse
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause) {
		IntByteConvert speed_byte(speed);
		IntByteConvert pause_byte(pause);
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetSpeed,
			section_num,
			speed_byte.index_0,
			speed_byte.index_1,
			pause_byte.index_0,
			pause_byte.index_1
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::run(Maestro *maestro, unsigned char *cue) {
		Animation* animation = maestro->get_section(cue[Cue::payload_index_ + 2])->get_animation();
		switch((Action)cue[Cue::payload_index_ + 1]) {
			case Action::SetColors:
				{
					unsigned char num_colors = cue[Cue::payload_index_ + 3];
					unsigned char current_color_index = 4;
					Colors::RGB colors[num_colors];
					for (unsigned char i = 0; i < num_colors; i++) {
						colors[i].r = cue[Cue::payload_index_ + current_color_index];
						current_color_index++;
						colors[i].g = cue[Cue::payload_index_ + current_color_index];
						current_color_index++;
						colors[i].b = cue[Cue::payload_index_ + current_color_index];
						current_color_index++;
					}
					animation->set_colors(colors, num_colors);
				}
				break;
			case Action::SetCycleIndex:
				animation->set_cycle_index(cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetFade:
				animation->set_fade(cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetOrientation:
				animation->set_orientation((Animation::Orientation)cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetReverse:
				animation->set_reverse(cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetSpeed:
				animation->set_speed(
					IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 3], cue[Cue::payload_index_ + 4]),
					IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 5], cue[Cue::payload_index_ + 6]));
				break;
		}
	}
}
