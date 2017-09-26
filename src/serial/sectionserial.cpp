#include "serial.h"
#include "sectionserial.h"

namespace PixelMaestro {
	void SectionSerial::add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type) {
		unsigned char payload[] {
			(unsigned char)Serial::Component::Section,
			Action::AddCanvas,
			section_num,
			canvas_type
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void SectionSerial::add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha) {
		unsigned char payload[] {
			(unsigned char)Serial::Component::Section,
			Action::AddOverlay,
			section_num,
			mix_mode,
			alpha
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void SectionSerial::run(Maestro *maestro, unsigned char *buffer) {
		switch ((Action)buffer[Serial::payload_index_ + 1]) {
			case Action::AddCanvas:
				maestro->get_section(buffer[Serial::payload_index_ + 2])->add_canvas(CanvasType::Type(buffer[Serial::payload_index_ + 3]));
				break;
			case Action::AddOverlay:
				maestro->get_section(buffer[Serial::payload_index_ + 2])->add_overlay(Colors::MixMode(buffer[Serial::payload_index_ + 3]), buffer[Serial::payload_index_ + 4]);
				break;
			case Action::SetAnimation:
				break;
		}
	}
}
