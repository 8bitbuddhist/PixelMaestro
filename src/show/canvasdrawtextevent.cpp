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
	CanvasDrawTextEvent::CanvasDrawTextEvent(unsigned long time, Canvas* canvas, unsigned short origin_x, unsigned short origin_y, Font* font, char* text) : Event(time) {
		this->canvas_ = canvas;
		this->origin_x_ = origin_x;
		this->origin_y_ = origin_y;
		this->font_ = font;
		this->text_ = text;
	}

	void CanvasDrawTextEvent::run() {
		canvas_->draw_text(origin_x_, origin_y_, font_, text_);
	}
}
