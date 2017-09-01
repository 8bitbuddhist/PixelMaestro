#include "canvasdrawpointevent.h"

namespace PixelMaestro {
	CanvasDrawPointEvent::CanvasDrawPointEvent(unsigned long time, Canvas *canvas, Point* cursor) : Event(time) {
		this->canvas_ = canvas;
		this->cursor_ = cursor;
	}

	void CanvasDrawPointEvent::run() {
		canvas_->draw_point(cursor_);
	}
}
