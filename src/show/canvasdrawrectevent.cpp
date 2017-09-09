#include "canvasdrawrectevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a rectangle onto a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param origin The starting point of the rectangle.
	 * @param size The size of the rectangle.
	 * @param fill Whether or not to fill the rectangle.
	 */
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
