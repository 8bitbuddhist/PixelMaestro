#include "canvasdrawtextevent.h"

namespace PixelMaestro {
	CanvasDrawTextEvent::CanvasDrawTextEvent(unsigned long time, Canvas* canvas, Point* origin, Font* font, char* text, unsigned int num_chars) : Event(time) {
		this->canvas_ = canvas;
		this->origin_ = origin;
		this->font_ = font;
		this->text_ = text;
		this->num_chars_ = num_chars;
	}

	void CanvasDrawTextEvent::run() {
		canvas_->draw_text(origin_, font_, text_, num_chars_);
	}
}
