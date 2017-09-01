#include "canvasdrawcircleevent.h"

namespace PixelMaestro {
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
