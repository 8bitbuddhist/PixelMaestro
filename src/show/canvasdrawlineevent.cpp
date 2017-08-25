#include "canvasdrawlineevent.h"

namespace PixelMaestro {
	CanvasDrawLineEvent::CanvasDrawLineEvent(unsigned long time, Canvas *canvas, Point *origin, Point *target) : Event(time){
		this->canvas_ = canvas;
		this->origin_ = origin;
		this->target_ = target;
	}

	void CanvasDrawLineEvent::run() {
		canvas_->drawLine(origin_, target_);
	}
}
