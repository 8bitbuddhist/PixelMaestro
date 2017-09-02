#include "canvasdrawrectevent.h"

namespace PixelMaestro {
	CanvasDrawRectEvent::CanvasDrawRectEvent(unsigned long time, Canvas* canvas, Point* origin, Point* size, bool fill) : Event(time)	{
		this->canvas_ = canvas;
		this->origin_ = origin;
		this->size_ = size;
		this->fill_ = fill;
	}

	void CanvasDrawRectEvent::run() {
		canvas_->draw_rect(origin_, size_, fill_);
	}
}
