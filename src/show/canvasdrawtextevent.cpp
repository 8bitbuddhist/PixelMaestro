#include "canvasdrawtextevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws text onto a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param origin The starting point of the text.
	 * @param font The font to use.
	 * @param text The text to draw.
	 */
	CanvasDrawTextEvent::CanvasDrawTextEvent(unsigned long time, Canvas* canvas, Point* origin, Font* font, char* text) : Event(time) {
		this->canvas_ = canvas;
		this->origin_ = origin;
		this->font_ = font;
		this->text_ = text;
	}

	void CanvasDrawTextEvent::run() {
		canvas_->draw_text(origin_, font_, text_);
	}
}
