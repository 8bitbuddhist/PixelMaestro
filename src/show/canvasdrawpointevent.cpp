#include "canvasdrawpointevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a single point on a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 */
	CanvasDrawPointEvent::CanvasDrawPointEvent(unsigned long time, BaseCanvas *canvas, unsigned short cursor_x, unsigned short cursor_y) : Event(time) {
		this->canvas_ = canvas;
		this->cursor_x_ = cursor_x;
		this->cursor_y_ = cursor_y;
	}

	void CanvasDrawPointEvent::run() {
		canvas_->draw_point(cursor_x_, cursor_y_);
	}
}
