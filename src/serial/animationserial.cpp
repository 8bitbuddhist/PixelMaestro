#include "animationserial.h"
#include "serial.h"

namespace PixelMaestro {
	void AnimationSerial::set_fade(unsigned char* buffer, unsigned char section_num, bool fade) {
		unsigned char payload[] {
			(unsigned char)Serial::Component::Animation,
			Action::SetFade,
			section_num,
			(unsigned char)fade
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void AnimationSerial::set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause) {
		IntByteConvert::IntAsByte speed_byte = IntByteConvert::int_to_byte(speed);
		IntByteConvert::IntAsByte pause_byte = IntByteConvert::int_to_byte(pause);
		unsigned char payload[] {
			(unsigned char)Serial::Component::Animation,
			Action::SetSpeed,
			section_num,
			speed_byte.quotient,
			speed_byte.remainder,
			pause_byte.quotient,
			pause_byte.remainder
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void AnimationSerial::run(Maestro *maestro, unsigned char *buffer) {
		switch((Action)buffer[Serial::payload_index_]) {
			case Action::SetFade:
				maestro->get_section(buffer[Serial::payload_index_ + 1])->get_animation()->set_fade(buffer[Serial::payload_index_ + 2]);
				break;
			case Action::SetSpeed:
				{
					unsigned short speed = IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 2], buffer[Serial::payload_index_ + 3]);
					unsigned short pause = IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 4], buffer[Serial::payload_index_ + 5]);
					maestro->get_section(buffer[Serial::payload_index_ + 1])->get_animation()->set_speed(speed, pause);
				}
				break;
		}
	}
}
