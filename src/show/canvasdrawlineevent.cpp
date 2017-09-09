#include "canvasdrawlineevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a line on a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param origin The starting point of the line.
	 * @param target The ending point of the line.
	 */
	CanvasDrawLineEvent::CanvasDrawLineEvent(unsigned long time, Canvas* canvas, Point* origin, Point* target) : Event(time){
		this->canvas_ = canvas;
		this->origin_ = origin;
		this->target_ = target;
	}

	void CanvasDrawLineEvent::run() {
		canvas_->draw_line(origin_, target_);
	}
}
