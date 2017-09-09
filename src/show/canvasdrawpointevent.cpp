#include "canvasdrawpointevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a single point on a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param cursor Where to draw the point.
	 */
	CanvasDrawPointEvent::CanvasDrawPointEvent(unsigned long time, Canvas *canvas, Point* cursor) : Event(time) {
		this->canvas_ = canvas;
		this->cursor_ = cursor;
	}

	void CanvasDrawPointEvent::run() {
		canvas_->draw_point(cursor_);
	}
}
