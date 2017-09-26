#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "../canvas/fonts/font5x8.h"
#include "canvasserial.h"
#include "serial.h"

namespace PixelMaestro {
	void CanvasSerial::draw_circle(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert radius_byte = IntByteConvert(radius);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawCircle,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.quotient_,
			origin_x_byte.remainder_,
			origin_y_byte.quotient_,
			origin_y_byte.remainder_,
			radius_byte.quotient_,
			radius_byte.remainder_,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_circle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert radius_byte = IntByteConvert(radius);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawCircle,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.quotient_,
			origin_x_byte.remainder_,
			origin_y_byte.quotient_,
			origin_y_byte.remainder_,
			radius_byte.quotient_,
			radius_byte.remainder_,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_line(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert target_x_byte = IntByteConvert(target_x);
		IntByteConvert target_y_byte = IntByteConvert(target_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawLine,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.quotient_,
			origin_x_byte.remainder_,
			origin_y_byte.quotient_,
			origin_y_byte.remainder_,
			target_x_byte.quotient_,
			target_x_byte.remainder_,
			target_y_byte.quotient_,
			target_y_byte.remainder_
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_line(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert target_x_byte = IntByteConvert(target_x);
		IntByteConvert target_y_byte = IntByteConvert(target_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawLine,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.quotient_,
			origin_x_byte.remainder_,
			origin_y_byte.quotient_,
			origin_y_byte.remainder_,
			target_x_byte.quotient_,
			target_x_byte.remainder_,
			target_y_byte.quotient_,
			target_y_byte.remainder_
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_point(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawPoint,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			x_byte.quotient_,
			x_byte.remainder_,
			y_byte.quotient_,
			y_byte.remainder_
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_point(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawPoint,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			x_byte.quotient_,
			x_byte.remainder_,
			y_byte.quotient_,
			y_byte.remainder_
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_rect(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert size_x_byte = IntByteConvert(size_x);
		IntByteConvert size_y_byte = IntByteConvert(size_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawRect,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.quotient_,
			origin_x_byte.remainder_,
			origin_y_byte.quotient_,
			origin_y_byte.remainder_,
			size_x_byte.quotient_,
			size_x_byte.remainder_,
			size_y_byte.quotient_,
			size_y_byte.remainder_,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_rect(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert size_x_byte = IntByteConvert(size_x);
		IntByteConvert size_y_byte = IntByteConvert(size_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawRect,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.quotient_,
			origin_x_byte.remainder_,
			origin_y_byte.quotient_,
			origin_y_byte.remainder_,
			size_x_byte.quotient_,
			size_x_byte.remainder_,
			size_y_byte.quotient_,
			size_y_byte.remainder_,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_triangle(unsigned char *buffer, unsigned char section_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte = IntByteConvert(point_a_x);
		IntByteConvert point_a_y_byte = IntByteConvert(point_a_y);
		IntByteConvert point_b_x_byte = IntByteConvert(point_b_x);
		IntByteConvert point_b_y_byte = IntByteConvert(point_b_y);
		IntByteConvert point_c_x_byte = IntByteConvert(point_c_x);
		IntByteConvert point_c_y_byte = IntByteConvert(point_c_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawTriangle,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			point_a_x_byte.quotient_,
			point_a_x_byte.remainder_,
			point_a_y_byte.quotient_,
			point_a_y_byte.remainder_,
			point_b_x_byte.quotient_,
			point_b_x_byte.remainder_,
			point_b_y_byte.quotient_,
			point_b_y_byte.remainder_,
			point_c_x_byte.quotient_,
			point_c_x_byte.remainder_,
			point_c_y_byte.quotient_,
			point_c_y_byte.remainder_,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_triangle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte = IntByteConvert(point_a_x);
		IntByteConvert point_a_y_byte = IntByteConvert(point_a_y);
		IntByteConvert point_b_x_byte = IntByteConvert(point_b_x);
		IntByteConvert point_b_y_byte = IntByteConvert(point_b_y);
		IntByteConvert point_c_x_byte = IntByteConvert(point_c_x);
		IntByteConvert point_c_y_byte = IntByteConvert(point_c_y);

		unsigned char payload[] {
			(unsigned char)Serial::Component::Canvas,
			(unsigned char)Action::DrawTriangle,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			point_a_x_byte.quotient_,
			point_a_x_byte.remainder_,
			point_a_y_byte.quotient_,
			point_a_y_byte.remainder_,
			point_b_x_byte.quotient_,
			point_b_x_byte.remainder_,
			point_b_y_byte.quotient_,
			point_b_y_byte.remainder_,
			point_c_x_byte.quotient_,
			point_c_x_byte.remainder_,
			point_c_y_byte.quotient_,
			point_c_y_byte.remainder_,
			(unsigned char)fill
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_text(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);

		unsigned char payload[10 + num_chars];
		payload[0] = (unsigned char)Serial::Component::Canvas;
		payload[1] = (unsigned char)Action::DrawText;
		payload[2] = (unsigned char)CanvasType::AnimationCanvas;
		payload[3] = section_num;
		payload[4] = origin_x_byte.quotient_;
		payload[5] = origin_x_byte.remainder_;
		payload[6] = origin_y_byte.quotient_;
		payload[7] = origin_y_byte.remainder_;
		payload[8] = (unsigned char)font;
		payload[9] = num_chars;

		for (int i = 0; i < num_chars; i++) {
			payload[10 + i] = text[i];
		}

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void CanvasSerial::draw_text(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);

		unsigned char payload[13 + num_chars];
		payload[0] = (unsigned char)Serial::Component::Canvas;
		payload[1] = (unsigned char)Action::DrawText;
		payload[2] = (unsigned char)CanvasType::AnimationCanvas;
		payload[3] = section_num;
		payload[4] = color.r;
		payload[5] = color.g;
		payload[6] = color.b;
		payload[7] = origin_x_byte.quotient_;
		payload[8] = origin_x_byte.remainder_;
		payload[9] = origin_y_byte.quotient_;
		payload[10] = origin_y_byte.remainder_;
		payload[11] = (unsigned char)font;
		payload[12] = num_chars;

		for (int i = 0; i < num_chars; i++) {
			payload[13 + i] = text[i];
		}

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
				case Action::DrawText:
					{
						int num_chars = buffer[Serial::payload_index_ + 9];

						// TODO: There has to be a better way to do this.
						Font* font;
						switch ((Font::Type)buffer[Serial::payload_index_ + 8]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						canvas->draw_text(
							IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 5], buffer[Serial::payload_index_ + 6]),
							IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]),
							font,
							// FIXME: unsigned char for text param?
							(char*)&buffer[Serial::payload_index_ + 10],
							num_chars
						);
					}
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
				case Action::DrawText:
					{
						int num_chars = buffer[Serial::payload_index_ + 12];

						// TODO: There has to be a better way to do this.
						Font* font;
						switch ((Font::Type)buffer[Serial::payload_index_ + 11]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						Colors::RGB color = {
							buffer[Serial::payload_index_ + 4],
							buffer[Serial::payload_index_ + 5],
							buffer[Serial::payload_index_ + 6]
						};

						canvas->draw_text(
							color,
							IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 7], buffer[Serial::payload_index_ + 8]),
							IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 9], buffer[Serial::payload_index_ + 10]),
							font,
							(char*)&buffer[Serial::payload_index_ + 13],
							num_chars
						);
					}
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
