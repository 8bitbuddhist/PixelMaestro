#include "canvasdrawcircleevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a circle on a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param origin The circle's starting point.
	 * @param radius The size of the circle.
	 * @param fill Whether or not to fill the circle.
	 */
	CanvasDrawCircleEvent::CanvasDrawCircleEvent(unsigned long time, Canvas* canvas, Point* origin, unsigned short radius, bool fill) : Event(time) {
		this->canvas_ = canvas;
		this->origin_ = origin;
		this->radius_ = radius;
		this->fill_ = fill;
	}

	void CanvasDrawCircleEvent::run() {
		canvas_->draw_circle(origin_, radius_, fill_);
	}
}
