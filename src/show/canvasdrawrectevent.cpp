#include "canvasdrawrectevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a rectangle onto a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param origin_x Top-left corner x coordinate.
	 * @param origin_y Top-left corner y coordinate.
	 * @param size_x Width of the rectangle.
	 * @param size_y Height of the rectangle.
	 * @param fill Whether or not to fill the rectangle.
	 */
	CanvasDrawRectEvent::CanvasDrawRectEvent(unsigned long time, Canvas* canvas, unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) : Event(time)	{
		this->canvas_ = canvas;
		this->origin_x_ = origin_x;
		this->origin_y_ = origin_y;
		this->size_x_ = size_x;
		this->size_y_ = size_y;
		this->fill_ = fill;
	}

	void CanvasDrawRectEvent::run() {
		canvas_->draw_rect(origin_x_, origin_y_, size_x_, size_y_, fill_);
	}
}
