#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "../canvas/fonts/font5x8.h"
#include "canvascommand.h"
#include "command.h"

namespace PixelMaestro {
	void CanvasCommand::draw_circle(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert radius_byte = IntByteConvert(radius);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawCircle,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.index_0,
			origin_x_byte.index_1,
			origin_y_byte.index_0,
			origin_y_byte.index_1,
			radius_byte.index_0,
			radius_byte.index_1,
			(unsigned char)fill
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_circle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert radius_byte = IntByteConvert(radius);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawCircle,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.index_0,
			origin_x_byte.index_1,
			origin_y_byte.index_0,
			origin_y_byte.index_1,
			radius_byte.index_0,
			radius_byte.index_1,
			(unsigned char)fill
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_line(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert target_x_byte = IntByteConvert(target_x);
		IntByteConvert target_y_byte = IntByteConvert(target_y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawLine,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.index_0,
			origin_x_byte.index_1,
			origin_y_byte.index_0,
			origin_y_byte.index_1,
			target_x_byte.index_0,
			target_x_byte.index_1,
			target_y_byte.index_0,
			target_y_byte.index_1
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_line(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert target_x_byte = IntByteConvert(target_x);
		IntByteConvert target_y_byte = IntByteConvert(target_y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawLine,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.index_0,
			origin_x_byte.index_1,
			origin_y_byte.index_0,
			origin_y_byte.index_1,
			target_x_byte.index_0,
			target_x_byte.index_1,
			target_y_byte.index_0,
			target_y_byte.index_1
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_point(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawPoint,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			x_byte.index_0,
			x_byte.index_1,
			y_byte.index_0,
			y_byte.index_1
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_point(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawPoint,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			x_byte.index_0,
			x_byte.index_1,
			y_byte.index_0,
			y_byte.index_1
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_rect(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert size_x_byte = IntByteConvert(size_x);
		IntByteConvert size_y_byte = IntByteConvert(size_y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawRect,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			origin_x_byte.index_0,
			origin_x_byte.index_1,
			origin_y_byte.index_0,
			origin_y_byte.index_1,
			size_x_byte.index_0,
			size_x_byte.index_1,
			size_y_byte.index_0,
			size_y_byte.index_1,
			(unsigned char)fill
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_rect(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);
		IntByteConvert size_x_byte = IntByteConvert(size_x);
		IntByteConvert size_y_byte = IntByteConvert(size_y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawRect,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			origin_x_byte.index_0,
			origin_x_byte.index_1,
			origin_y_byte.index_0,
			origin_y_byte.index_1,
			size_x_byte.index_0,
			size_x_byte.index_1,
			size_y_byte.index_0,
			size_y_byte.index_1,
			(unsigned char)fill
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_triangle(unsigned char *buffer, unsigned char section_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte = IntByteConvert(point_a_x);
		IntByteConvert point_a_y_byte = IntByteConvert(point_a_y);
		IntByteConvert point_b_x_byte = IntByteConvert(point_b_x);
		IntByteConvert point_b_y_byte = IntByteConvert(point_b_y);
		IntByteConvert point_c_x_byte = IntByteConvert(point_c_x);
		IntByteConvert point_c_y_byte = IntByteConvert(point_c_y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawTriangle,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			point_a_x_byte.index_0,
			point_a_x_byte.index_1,
			point_a_y_byte.index_0,
			point_a_y_byte.index_1,
			point_b_x_byte.index_0,
			point_b_x_byte.index_1,
			point_b_y_byte.index_0,
			point_b_y_byte.index_1,
			point_c_x_byte.index_0,
			point_c_x_byte.index_1,
			point_c_y_byte.index_0,
			point_c_y_byte.index_1,
			(unsigned char)fill
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_triangle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte = IntByteConvert(point_a_x);
		IntByteConvert point_a_y_byte = IntByteConvert(point_a_y);
		IntByteConvert point_b_x_byte = IntByteConvert(point_b_x);
		IntByteConvert point_b_y_byte = IntByteConvert(point_b_y);
		IntByteConvert point_c_x_byte = IntByteConvert(point_c_x);
		IntByteConvert point_c_y_byte = IntByteConvert(point_c_y);

		unsigned char payload[] {
			(unsigned char)Command::Component::Canvas,
			(unsigned char)Action::DrawTriangle,
			(unsigned char)CanvasType::ColorCanvas,
			section_num,
			color.r,
			color.g,
			color.b,
			point_a_x_byte.index_0,
			point_a_x_byte.index_1,
			point_a_y_byte.index_0,
			point_a_y_byte.index_1,
			point_b_x_byte.index_0,
			point_b_x_byte.index_1,
			point_b_y_byte.index_0,
			point_b_y_byte.index_1,
			point_c_x_byte.index_0,
			point_c_x_byte.index_1,
			point_c_y_byte.index_0,
			point_c_y_byte.index_1,
			(unsigned char)fill
		};

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_text(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);

		unsigned char payload[10 + num_chars];
		payload[0] = (unsigned char)Command::Component::Canvas;
		payload[1] = (unsigned char)Action::DrawText;
		payload[2] = (unsigned char)CanvasType::AnimationCanvas;
		payload[3] = section_num;
		payload[4] = origin_x_byte.index_0;
		payload[5] = origin_x_byte.index_1;
		payload[6] = origin_y_byte.index_0;
		payload[7] = origin_y_byte.index_1;
		payload[8] = (unsigned char)font;
		payload[9] = num_chars;

		for (int i = 0; i < num_chars; i++) {
			payload[10 + i] = text[i];
		}

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::draw_text(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte = IntByteConvert(origin_x);
		IntByteConvert origin_y_byte = IntByteConvert(origin_y);

		unsigned char payload[13 + num_chars];
		payload[0] = (unsigned char)Command::Component::Canvas;
		payload[1] = (unsigned char)Action::DrawText;
		payload[2] = (unsigned char)CanvasType::AnimationCanvas;
		payload[3] = section_num;
		payload[4] = color.r;
		payload[5] = color.g;
		payload[6] = color.b;
		payload[7] = origin_x_byte.index_0;
		payload[8] = origin_x_byte.index_1;
		payload[9] = origin_y_byte.index_0;
		payload[10] = origin_y_byte.index_1;
		payload[11] = (unsigned char)font;
		payload[12] = num_chars;

		for (int i = 0; i < num_chars; i++) {
			payload[13 + i] = text[i];
		}

		Command::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCommand::run(Maestro *maestro, unsigned char *buffer) {
		if ((CanvasType::Type)buffer[Command::payload_index_ + 2] == CanvasType::AnimationCanvas) {
			AnimationCanvas* canvas = static_cast<AnimationCanvas*>(maestro->get_section(buffer[Command::payload_index_ + 3])->get_canvas());
			switch((Action)buffer[Command::payload_index_ + 1]) {
				case Action::DrawCircle:
					canvas->draw_circle(
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 4], buffer[Command::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 6],	buffer[Command::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 8], buffer[Command::payload_index_ + 9]),
						(bool)buffer[Command::payload_index_ + 10]);
					break;
				case Action::DrawLine:
					canvas->draw_line(
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 4], buffer[Command::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 6], buffer[Command::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 8], buffer[Command::payload_index_ + 9]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 10], buffer[Command::payload_index_ + 11]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 4], buffer[Command::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 6], buffer[Command::payload_index_ + 7]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 4], buffer[Command::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 6],	buffer[Command::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 8], buffer[Command::payload_index_ + 9]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 10], buffer[Command::payload_index_ + 11]),
						(bool)buffer[Command::payload_index_ + 12]);
					break;
				case Action::DrawText:
					{
						int num_chars = buffer[Command::payload_index_ + 9];

						// TODO: There has to be a better way to handle this.
						Font* font;
						switch ((Font::Type)buffer[Command::payload_index_ + 8]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						canvas->draw_text(
							IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 5], buffer[Command::payload_index_ + 6]),
							IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 7], buffer[Command::payload_index_ + 8]),
							font,
							(char*)&buffer[Command::payload_index_ + 10],
							num_chars
						);

						delete font;
					}
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 4], buffer[Command::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 6],	buffer[Command::payload_index_ + 7]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 8], buffer[Command::payload_index_ + 9]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 10], buffer[Command::payload_index_ + 11]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 12], buffer[Command::payload_index_ + 13]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 14], buffer[Command::payload_index_ + 15]),
						(bool)buffer[Command::payload_index_ + 16]);
					break;
			}
		}
		else if ((CanvasType::Type)buffer[Command::payload_index_ + 2] == CanvasType::ColorCanvas) {
			ColorCanvas* canvas = static_cast<ColorCanvas*>(maestro->get_section(buffer[Command::payload_index_ + 3])->get_canvas());
			Colors::RGB color = {
				buffer[Command::payload_index_ + 4],
				buffer[Command::payload_index_ + 5],
				buffer[Command::payload_index_ + 6]
			};
			switch((Action)buffer[Command::payload_index_ + 1]) {
				case Action::DrawCircle:
					canvas->draw_circle(
						color,
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 7], buffer[Command::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 9], buffer[Command::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 11], buffer[Command::payload_index_ + 12]),
						bool(buffer[Command::payload_index_ + 13]));
					break;
				case Action::DrawLine:
					canvas->draw_line(
						color,
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 7], buffer[Command::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 9], buffer[Command::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 11], buffer[Command::payload_index_ + 12]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 13], buffer[Command::payload_index_ + 14]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						color,
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 4], buffer[Command::payload_index_ + 5]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 6], buffer[Command::payload_index_ + 7]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						color,
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 7], buffer[Command::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 9], buffer[Command::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 11], buffer[Command::payload_index_ + 12]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 13], buffer[Command::payload_index_ + 14]),
						bool(buffer[Command::payload_index_ + 15]));
					break;
				case Action::DrawText:
					{
						int num_chars = buffer[Command::payload_index_ + 12];

						// See AnimationCanvas::DrawText
						Font* font;
						switch ((Font::Type)buffer[Command::payload_index_ + 11]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						Colors::RGB color = {
							buffer[Command::payload_index_ + 4],
							buffer[Command::payload_index_ + 5],
							buffer[Command::payload_index_ + 6]
						};

						canvas->draw_text(
							color,
							IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 7], buffer[Command::payload_index_ + 8]),
							IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 9], buffer[Command::payload_index_ + 10]),
							font,
							(char*)&buffer[Command::payload_index_ + 13],
							num_chars
						);

						delete font;
					}
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						color,
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 7], buffer[Command::payload_index_ + 8]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 9], buffer[Command::payload_index_ + 10]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 11], buffer[Command::payload_index_ + 12]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 13], buffer[Command::payload_index_ + 14]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 15], buffer[Command::payload_index_ + 16]),
						IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 17], buffer[Command::payload_index_ + 18]),
						bool(buffer[Command::payload_index_ + 19]));
					break;
			}
		}
	}
}
