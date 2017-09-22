#include "canvasdrawlineevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a line on a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 * @param target_x Ending point x coordinate.
	 * @param target_y Ending point y coordinate.
	 */
	CanvasDrawLineEvent::CanvasDrawLineEvent(unsigned long time, BaseCanvas* canvas, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) : Event(time){
		this->canvas_ = canvas;
		this->origin_x_ = origin_x;
		this->origin_y_ = origin_y;
		this->target_x_ = target_x;
		this->target_y_ = target_y;
	}

	void CanvasDrawLineEvent::run() {
		canvas_->draw_line(origin_x_, origin_y_, target_x_, target_y_);
	}
}
