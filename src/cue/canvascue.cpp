#include "../canvas/animationcanvas.h"
#include "../canvas/colorcanvas.h"
#include "../canvas/fonts/font5x8.h"
#include "canvascue.h"
#include "cue.h"

namespace PixelMaestro {
	void CanvasCue::draw_circle(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_circle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert radius_byte(radius);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_line(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_line(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert target_x_byte(target_x);
		IntByteConvert target_y_byte(target_y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_point(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
			(unsigned char)Action::DrawPoint,
			(unsigned char)CanvasType::AnimationCanvas,
			section_num,
			x_byte.index_0,
			x_byte.index_1,
			y_byte.index_0,
			y_byte.index_1
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_point(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short x, unsigned short y) {
		IntByteConvert x_byte(x);
		IntByteConvert y_byte(y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_rect(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_rect(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);
		IntByteConvert size_x_byte(size_x);
		IntByteConvert size_y_byte(size_y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_triangle(unsigned char *buffer, unsigned char section_num, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_triangle(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
		IntByteConvert point_a_x_byte(point_a_x);
		IntByteConvert point_a_y_byte(point_a_y);
		IntByteConvert point_b_x_byte(point_b_x);
		IntByteConvert point_b_y_byte(point_b_y);
		IntByteConvert point_c_x_byte(point_c_x);
		IntByteConvert point_c_y_byte(point_c_y);

		unsigned char payload[] {
			(unsigned char)Cue::Component::Canvas,
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_text(unsigned char *buffer, unsigned char section_num, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		unsigned char font_index = 10;
		unsigned char payload[font_index + num_chars];
		payload[0] = (unsigned char)Cue::Component::Canvas;
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
			payload[font_index + i] = text[i];
		}

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::draw_text(unsigned char *buffer, unsigned char section_num, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font::Type font, const char *text, unsigned char num_chars) {
		IntByteConvert origin_x_byte(origin_x);
		IntByteConvert origin_y_byte(origin_y);

		unsigned char payload[13 + num_chars];
		payload[0] = (unsigned char)Cue::Component::Canvas;
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

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void CanvasCue::run(Maestro *maestro, unsigned char *cue) {
		CanvasType::Type canvas_type = (CanvasType::Type)cue[Cue::payload_index_ + 2];
		if (canvas_type == CanvasType::AnimationCanvas) {
			AnimationCanvas* canvas = static_cast<AnimationCanvas*>(maestro->get_section(cue[Cue::payload_index_ + 3])->get_canvas());
			switch((Action)cue[Cue::payload_index_ + 1]) {
				case Action::DrawCircle:
					canvas->draw_circle(
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 4], cue[Cue::payload_index_ + 5]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 6], cue[Cue::payload_index_ + 7]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 8], cue[Cue::payload_index_ + 9]),
						(bool)cue[Cue::payload_index_ + 10]);
					break;
				case Action::DrawLine:
					canvas->draw_line(
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 4], cue[Cue::payload_index_ + 5]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 6], cue[Cue::payload_index_ + 7]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 8], cue[Cue::payload_index_ + 9]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 10], cue[Cue::payload_index_ + 11]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 4], cue[Cue::payload_index_ + 5]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 6], cue[Cue::payload_index_ + 7]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 4], cue[Cue::payload_index_ + 5]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 6], cue[Cue::payload_index_ + 7]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 8], cue[Cue::payload_index_ + 9]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 10], cue[Cue::payload_index_ + 11]),
						(bool)cue[Cue::payload_index_ + 12]);
					break;
				case Action::DrawText:
					{
						// TODO: There must be a better way to handle this.
						Font* font;
						switch ((Font::Type)cue[Cue::payload_index_ + 8]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						canvas->draw_text(
							IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 5], cue[Cue::payload_index_ + 6]),
							IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 7], cue[Cue::payload_index_ + 8]),
							font,
							(char*)&cue[Cue::payload_index_ + 10],
							cue[Cue::payload_index_ + 9]
						);

						delete font;
					}
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 4], cue[Cue::payload_index_ + 5]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 6], cue[Cue::payload_index_ + 7]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 8], cue[Cue::payload_index_ + 9]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 10], cue[Cue::payload_index_ + 11]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 12], cue[Cue::payload_index_ + 13]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 14], cue[Cue::payload_index_ + 15]),
						(bool)cue[Cue::payload_index_ + 16]);
					break;
			}
		}
		else if (canvas_type == CanvasType::ColorCanvas) {
			ColorCanvas* canvas = static_cast<ColorCanvas*>(maestro->get_section(cue[Cue::payload_index_ + 3])->get_canvas());
			Colors::RGB color = {
				cue[Cue::payload_index_ + 4],
				cue[Cue::payload_index_ + 5],
				cue[Cue::payload_index_ + 6]
			};
			switch((Action)cue[Cue::payload_index_ + 1]) {
				case Action::DrawCircle:
					canvas->draw_circle(
						color,
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 7], cue[Cue::payload_index_ + 8]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 9], cue[Cue::payload_index_ + 10]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 11], cue[Cue::payload_index_ + 12]),
						bool(cue[Cue::payload_index_ + 13]));
					break;
				case Action::DrawLine:
					canvas->draw_line(
						color,
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 7], cue[Cue::payload_index_ + 8]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 9], cue[Cue::payload_index_ + 10]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 11], cue[Cue::payload_index_ + 12]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 13], cue[Cue::payload_index_ + 14]));
					break;
				case Action::DrawPoint:
					canvas->draw_point(
						color,
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 4], cue[Cue::payload_index_ + 5]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 6], cue[Cue::payload_index_ + 7]));
					break;
				case Action::DrawRect:
					canvas->draw_rect(
						color,
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 7], cue[Cue::payload_index_ + 8]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 9], cue[Cue::payload_index_ + 10]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 11], cue[Cue::payload_index_ + 12]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 13], cue[Cue::payload_index_ + 14]),
						bool(cue[Cue::payload_index_ + 15]));
					break;
				case Action::DrawText:
					{
						// See AnimationCanvas::DrawText
						Font* font;
						switch ((Font::Type)cue[Cue::payload_index_ + 11]) {
							case Font::Type::Font5x8:
								font = new Font5x8();
								break;
						}

						Colors::RGB color = {
							cue[Cue::payload_index_ + 4],
							cue[Cue::payload_index_ + 5],
							cue[Cue::payload_index_ + 6]
						};

						canvas->draw_text(
							color,
							IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 7], cue[Cue::payload_index_ + 8]),
							IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 9], cue[Cue::payload_index_ + 10]),
							font,
							(char*)&cue[Cue::payload_index_ + 13],
							cue[Cue::payload_index_ + 12]
						);

						delete font;
					}
					break;
				case Action::DrawTriangle:
					canvas->draw_triangle(
						color,
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 7], cue[Cue::payload_index_ + 8]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 9], cue[Cue::payload_index_ + 10]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 11], cue[Cue::payload_index_ + 12]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 13], cue[Cue::payload_index_ + 14]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 15], cue[Cue::payload_index_ + 16]),
						IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 17], cue[Cue::payload_index_ + 18]),
						bool(cue[Cue::payload_index_ + 19]));
					break;
			}
		}
	}
}
