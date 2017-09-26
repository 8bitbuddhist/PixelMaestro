#include "animationserial.h"
#include "serial.h"

namespace PixelMaestro {
	void AnimationSerial::set_colors(unsigned char *buffer, unsigned char section_num, Colors::RGB *colors, unsigned char num_colors) {
		unsigned char payload[3 + (num_colors * 3)];
		payload[0] = (unsigned char)Serial::Component::Animation;
		payload[1] = (unsigned char)Action::SetColors;
		payload[2] = section_num;
		payload[3] = num_colors;

		int colors_index = 4;
		for (unsigned char i = 0; i < num_colors; i++) {
			payload[colors_index] = colors[i].r;
			colors_index++;
			payload[colors_index] = colors[i].g;
			colors_index++;
			payload[colors_index] = colors[i].b;
			colors_index++;
		}

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void AnimationSerial::set_fade(unsigned char* buffer, unsigned char section_num, bool fade) {
		unsigned char payload[] {
			(unsigned char)Serial::Component::Animation,
			(unsigned char)Action::SetFade,
			section_num,
			(unsigned char)fade
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void AnimationSerial::set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause) {
		IntByteConvert speed_byte = IntByteConvert(speed);
		IntByteConvert pause_byte = IntByteConvert(pause);
		unsigned char payload[] {
			(unsigned char)Serial::Component::Animation,
			(unsigned char)Action::SetSpeed,
			section_num,
			speed_byte.quotient_,
			speed_byte.remainder_,
			pause_byte.quotient_,
			pause_byte.remainder_
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void AnimationSerial::run(Maestro *maestro, unsigned char *buffer) {
		Animation* animation = maestro->get_section(buffer[Serial::payload_index_ + 2])->get_animation();
		switch((Action)buffer[Serial::payload_index_ + 1]) {
			case Action::SetColors:
				{
					delete animation->get_colors();

					int num_colors = buffer[Serial::payload_index_ + 3];
					int current_color_index = 4;
					Colors::RGB* colors = new Colors::RGB[num_colors];
					for (unsigned char i = 0; i < num_colors; i++) {
						colors[i].r = buffer[Serial::payload_index_ + current_color_index];
						current_color_index++;
						colors[i].g = buffer[Serial::payload_index_ + current_color_index];
						current_color_index++;
						colors[i].b = buffer[Serial::payload_index_ + current_color_index];
						current_color_index++;
					}
					animation->set_colors(colors, num_colors);
				}
				break;
			case Action::SetFade:
				animation->set_fade(buffer[Serial::payload_index_ + 3]);
				break;
			case Action::SetSpeed:
				{
					unsigned short speed = IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 3], buffer[Serial::payload_index_ + 4]);
					unsigned short pause = IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 5], buffer[Serial::payload_index_ + 6]);
					animation->set_speed(speed, pause);
				}
				break;
		}
	}
}
