#include "canvasdrawtriangleevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a triangle on a Canvas. Points are drawn clockwise.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param point_a The first point in the triangle.
	 * @param point_b The second point in the triangle.
	 * @param point_c The third point in the triangle.
	 * @param fill Whether to fill the triangle.
	 */
	CanvasDrawTriangleEvent::CanvasDrawTriangleEvent(unsigned long time, Canvas* canvas, Point* point_a, Point* point_b, Point* point_c, bool fill) : Event(time) {
		this->canvas_ = canvas;
		this->point_a_ = point_a;
		this->point_b_ = point_b;
		this->point_c_ = point_c;
		this->fill_ = fill;
	}

	void CanvasDrawTriangleEvent::run() {
		canvas_->draw_triangle(point_a_, point_b_, point_c_, fill_);
	}
}
