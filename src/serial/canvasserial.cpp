#include "canvasserial.h"
#include "serial.h"
#include "canvas/animationcanvas.h"
#include "canvas/colorcanvas.h"

namespace PixelMaestro {
	void CanvasSerial::draw_circle(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert::IntAsByte origin_x_byte = IntByteConvert::int_to_byte(origin_x);
		IntByteConvert::IntAsByte origin_y_byte = IntByteConvert::int_to_byte(origin_y);
		IntByteConvert::IntAsByte radius_byte = IntByteConvert::int_to_byte(radius);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawCircle,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.quotient,
			origin_x_byte.remainder,
			origin_y_byte.quotient,
			origin_y_byte.remainder,
			radius_byte.quotient,
			radius_byte.remainder,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_circle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert::IntAsByte origin_x_byte = IntByteConvert::int_to_byte(origin_x);
		IntByteConvert::IntAsByte origin_y_byte = IntByteConvert::int_to_byte(origin_y);
		IntByteConvert::IntAsByte radius_byte = IntByteConvert::int_to_byte(radius);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawCircle,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.quotient,
			origin_x_byte.remainder,
			origin_y_byte.quotient,
			origin_y_byte.remainder,
			radius_byte.quotient,
			radius_byte.remainder,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::run(Maestro *maestro, unsigned char *buffer) {
		if ((CanvasType::Type)buffer[Serial::payload_index_ + 2] == CanvasType::AnimationCanvas) {
			AnimationCanvas* canvas = static_cast<AnimationCanvas*>(maestro->get_section(buffer[Serial::payload_index_ + 2])->get_canvas());
			switch((Action)buffer[Serial::payload_index_ + 1]) {
				case Action::DrawCircle:
					canvas->draw_circle(IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 3], buffer[Serial::payload_index_ + 4]), IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 5], buffer[Serial::payload_index_ + 6]), IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]), (bool)buffer[Serial::payload_index_ + 9]);
					break;
				case Action::DrawLine:
					break;
				case Action::DrawPoint:
					break;
				case Action::DrawRect:
					break;
				case Action::DrawTriangle:
					break;
			}
		}
		else if ((CanvasType::Type)buffer[Serial::payload_index_ + 2] == CanvasType::ColorCanvas) {
			ColorCanvas* canvas = static_cast<ColorCanvas*>(maestro->get_section(buffer[Serial::payload_index_ + 3])->get_canvas());
			Colors::RGB color = {
				buffer[Serial::payload_index_ + 4],
				buffer[Serial::payload_index_ + 5],
				buffer[Serial::payload_index_ + 6]
			};
			switch((Action)buffer[Serial::payload_index_ + 1]) {
				case Action::DrawCircle:
					canvas->draw_circle(color, IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]), IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 9], buffer[Serial::payload_index_ + 10]), IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 11], buffer[Serial::payload_index_ + 12]), bool(buffer[Serial::payload_index_ + 13]));
					break;
				case Action::DrawLine:
					break;
				case Action::DrawPoint:
					break;
				case Action::DrawRect:
					break;
				case Action::DrawTriangle:
					break;
			}
		}
	}
}
