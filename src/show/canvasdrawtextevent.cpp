#include "canvasdrawtextevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws text onto a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param origin_x Top-left x coordinate.
	 * @param origin_y Top-left y coordinate.
	 * @param font The font to use.
	 * @param text The text to draw.
	 */
	CanvasDrawTextEvent::CanvasDrawTextEvent(unsigned long time, Canvas* canvas, unsigned short origin_x, unsigned short origin_y, Font* font, char* text, unsigned char num_chars) : Event(time) {
		this->canvas_ = canvas;
		this->origin_x_ = origin_x;
		this->origin_y_ = origin_y;
		this->font_ = font;
		this->text_ = text;
		this->num_chars_ = num_chars;
	}

	/**
	 * Constructor. Draws text onto a ColorCanvas.
	 * @param time Time until the Event runs.
	 * @param canvas ColorCanvas to draw on.
	 * @param color Color to draw in.
	 * @param origin_x Top-left x coordinate.
	 * @param origin_y Top-left y coordinate.
	 * @param font The font to use.
	 * @param text The text to draw.
	 */
	CanvasDrawTextEvent::CanvasDrawTextEvent(unsigned long time, ColorCanvas* canvas, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font* font, char* text, unsigned char num_chars) : Event(time) {
		this->canvas_ = canvas;
		this->color_ = color;
		this->is_color_canvas_ = true;
		this->origin_x_ = origin_x;
		this->origin_y_ = origin_y;
		this->font_ = font;
		this->text_ = text;
		this->num_chars_ = num_chars;
	}

	void CanvasDrawTextEvent::run() {
		if (is_color_canvas_) {
			static_cast<ColorCanvas*>(canvas_)->draw_text(color_, origin_x_, origin_y_, font_, text_, num_chars_);
		}
		else {
			canvas_->draw_text(origin_x_, origin_y_, font_, text_, num_chars_);
		}
	}
}
