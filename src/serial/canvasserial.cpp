#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "canvasserial.h"
#include "serial.h"

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

	void CanvasSerial::draw_line(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert::IntAsByte origin_x_byte = IntByteConvert::int_to_byte(origin_x);
		IntByteConvert::IntAsByte origin_y_byte = IntByteConvert::int_to_byte(origin_y);
		IntByteConvert::IntAsByte target_x_byte = IntByteConvert::int_to_byte(target_x);
		IntByteConvert::IntAsByte target_y_byte = IntByteConvert::int_to_byte(target_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawLine,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.quotient,
			origin_x_byte.remainder,
			origin_y_byte.quotient,
			origin_y_byte.remainder,
			target_x_byte.quotient,
			target_x_byte.remainder,
			target_y_byte.quotient,
			target_y_byte.remainder
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_line(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert::IntAsByte origin_x_byte = IntByteConvert::int_to_byte(origin_x);
		IntByteConvert::IntAsByte origin_y_byte = IntByteConvert::int_to_byte(origin_y);
		IntByteConvert::IntAsByte target_x_byte = IntByteConvert::int_to_byte(target_x);
		IntByteConvert::IntAsByte target_y_byte = IntByteConvert::int_to_byte(target_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawLine,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.quotient,
			origin_x_byte.remainder,
			origin_y_byte.quotient,
			origin_y_byte.remainder,
			target_x_byte.quotient,
			target_x_byte.remainder,
			target_y_byte.quotient,
			target_y_byte.remainder
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_point(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert::IntAsByte x_byte = IntByteConvert::int_to_byte(x);
		IntByteConvert::IntAsByte y_byte = IntByteConvert::int_to_byte(y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawPoint,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			x_byte.quotient,
			x_byte.remainder,
			y_byte.quotient,
			y_byte.remainder
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_point(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short x, unsigned short y) {
		IntByteConvert::IntAsByte x_byte = IntByteConvert::int_to_byte(x);
		IntByteConvert::IntAsByte y_byte = IntByteConvert::int_to_byte(y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawPoint,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			x_byte.quotient,
			x_byte.remainder,
			y_byte.quotient,
			y_byte.remainder
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_rect(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert::IntAsByte origin_x_byte = IntByteConvert::int_to_byte(origin_x);
		IntByteConvert::IntAsByte origin_y_byte = IntByteConvert::int_to_byte(origin_y);
		IntByteConvert::IntAsByte size_x_byte = IntByteConvert::int_to_byte(size_x);
		IntByteConvert::IntAsByte size_y_byte = IntByteConvert::int_to_byte(size_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawRect,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.quotient,
			origin_x_byte.remainder,
			origin_y_byte.quotient,
			origin_y_byte.remainder,
			size_x_byte.quotient,
			size_x_byte.remainder,
			size_y_byte.quotient,
			size_y_byte.remainder,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_rect(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert::IntAsByte origin_x_byte = IntByteConvert::int_to_byte(origin_x);
		IntByteConvert::IntAsByte origin_y_byte = IntByteConvert::int_to_byte(origin_y);
		IntByteConvert::IntAsByte size_x_byte = IntByteConvert::int_to_byte(size_x);
		IntByteConvert::IntAsByte size_y_byte = IntByteConvert::int_to_byte(size_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawRect,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.quotient,
			origin_x_byte.remainder,
			origin_y_byte.quotient,
			origin_y_byte.remainder,
			size_x_byte.quotient,
			size_x_byte.remainder,
			size_y_byte.quotient,
			size_y_byte.remainder,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_triangle(unsigned char *buffer, unsigned char section_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert::IntAsByte point_a_x_byte = IntByteConvert::int_to_byte(point_a_x);
		IntByteConvert::IntAsByte point_a_y_byte = IntByteConvert::int_to_byte(point_a_y);
		IntByteConvert::IntAsByte point_b_x_byte = IntByteConvert::int_to_byte(point_b_x);
		IntByteConvert::IntAsByte point_b_y_byte = IntByteConvert::int_to_byte(point_b_y);
		IntByteConvert::IntAsByte point_c_x_byte = IntByteConvert::int_to_byte(point_c_x);
		IntByteConvert::IntAsByte point_c_y_byte = IntByteConvert::int_to_byte(point_c_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawTriangle,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			point_a_x_byte.quotient,
			point_a_x_byte.remainder,
			point_a_y_byte.quotient,
			point_a_y_byte.remainder,
			point_b_x_byte.quotient,
			point_b_x_byte.remainder,
			point_b_y_byte.quotient,
			point_b_y_byte.remainder,
			point_c_x_byte.quotient,
			point_c_x_byte.remainder,
			point_c_y_byte.quotient,
			point_c_y_byte.remainder,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_triangle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert::IntAsByte point_a_x_byte = IntByteConvert::int_to_byte(point_a_x);
		IntByteConvert::IntAsByte point_a_y_byte = IntByteConvert::int_to_byte(point_a_y);
		IntByteConvert::IntAsByte point_b_x_byte = IntByteConvert::int_to_byte(point_b_x);
		IntByteConvert::IntAsByte point_b_y_byte = IntByteConvert::int_to_byte(point_b_y);
		IntByteConvert::IntAsByte point_c_x_byte = IntByteConvert::int_to_byte(point_c_x);
		IntByteConvert::IntAsByte point_c_y_byte = IntByteConvert::int_to_byte(point_c_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawTriangle,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			point_a_x_byte.quotient,
			point_a_x_byte.remainder,
			point_a_y_byte.quotient,
			point_a_y_byte.remainder,
			point_b_x_byte.quotient,
			point_b_x_byte.remainder,
			point_b_y_byte.quotient,
			point_b_y_byte.remainder,
			point_c_x_byte.quotient,
			point_c_x_byte.remainder,
			point_c_y_byte.quotient,
			point_c_y_byte.remainder,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::run(Maestro *maestro, unsigned char *buffer) {
		if ((CanvasType::Type)buffer[Serial::payload_index_ + 2] == CanvasType::AnimationCanvas) {
			AnimationCanvas* canvas = static_cast<AnimationCanvas*>(maestro->get_section(buffer[Serial::payload_index_ + 3])->get_canvas());
			switch((Action)buffer[Serial::payload_index_ + 1]) {
				case Action::DrawCircle:
					canvas->draw_circle(
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 4], buffer[Serial::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 6],	buffer[Serial::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 8], buffer[Serial::payload_index_ + 9]),
						(bool)buffer[Serial::payload_index_ + 10]);
					break;
				case Action::DrawLine:
					canvas->draw_line(
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 4], buffer[Serial::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 6], buffer[Serial::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 8], buffer[Serial::payload_index_ + 9]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 10], buffer[Serial::payload_index_ + 11]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 4], buffer[Serial::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 6], buffer[Serial::payload_index_ + 7]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 4], buffer[Serial::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 6],	buffer[Serial::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 8], buffer[Serial::payload_index_ + 9]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 10], buffer[Serial::payload_index_ + 11]),
						(bool)buffer[Serial::payload_index_ + 12]);
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 4], buffer[Serial::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 6],	buffer[Serial::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 8], buffer[Serial::payload_index_ + 9]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 10], buffer[Serial::payload_index_ + 11]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 12], buffer[Serial::payload_index_ + 13]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 14], buffer[Serial::payload_index_ + 15]),
						(bool)buffer[Serial::payload_index_ + 16]);
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
					canvas->draw_circle(
						color,
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 9], buffer[Serial::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 11], buffer[Serial::payload_index_ + 12]),
						bool(buffer[Serial::payload_index_ + 13]));
					break;
				case Action::DrawLine:
					canvas->draw_line(
						color,
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 9], buffer[Serial::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 11], buffer[Serial::payload_index_ + 12]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 13], buffer[Serial::payload_index_ + 14]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						color,
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 4], buffer[Serial::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 6], buffer[Serial::payload_index_ + 7]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						color,
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 9], buffer[Serial::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 11], buffer[Serial::payload_index_ + 12]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 13], buffer[Serial::payload_index_ + 14]),
						bool(buffer[Serial::payload_index_ + 15]));
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						color,
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 9], buffer[Serial::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 11], buffer[Serial::payload_index_ + 12]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 13], buffer[Serial::payload_index_ + 14]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 15], buffer[Serial::payload_index_ + 16]),
						IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 17], buffer[Serial::payload_index_ + 18]),
						bool(buffer[Serial::payload_index_ + 19]));
					break;
			}
		}
	}
}
