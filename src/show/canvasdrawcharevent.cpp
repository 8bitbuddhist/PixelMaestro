#include "canvasdrawcharevent.h"

namespace PixelMaestro {
	CanvasDrawCharEvent::CanvasDrawCharEvent(unsigned long time, Canvas* canvas, Point* origin, Font* font, char character) : Event(time) {
		this->canvas_ = canvas;
		this->origin_ = origin;
		this->font_ = font;
		this->character_ = character;
	}

	void CanvasDrawCharEvent::run() {
		canvas_->draw_char(origin_, font_, character_);
	}
}
