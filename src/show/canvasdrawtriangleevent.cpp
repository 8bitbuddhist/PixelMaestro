#include "canvasdrawtriangleevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a triangle on a Canvas. Points are drawn clockwise.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param point_a_x First point x-coordinate.
	 * @param point_a_y First point y-coordinate.
	 * @param point_b_x Second point x-coordinate.
	 * @param point_b_y Second point y-coordinate.
	 * @param point_c_x Third point x-coordinate.
	 * @param point_c_y Third point y-coordinate.
	 * @param fill Whether to fill the triangle.
	 */
	CanvasDrawTriangleEvent::CanvasDrawTriangleEvent(unsigned long time, BaseCanvas* canvas, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) : Event(time) {
		this->canvas_ = canvas;
		this->point_a_x_ = point_a_x;
		this->point_a_y_ = point_a_y;
		this->point_b_x_ = point_b_x;
		this->point_b_y_ = point_b_y;
		this->point_c_x_ = point_c_x;
		this->point_c_y_ = point_c_y;
		this->fill_ = fill;
	}

	/**
	 * Constructor. Draws a triangle on a ColorCanvas. Points are drawn clockwise.
	 * @param time Time until the Event runs.
	 * @param canvas ColorCanvas to draw on.
	 * @param color Color to draw in.
	 * @param point_a_x First point x-coordinate.
	 * @param point_a_y First point y-coordinate.
	 * @param point_b_x Second point x-coordinate.
	 * @param point_b_y Second point y-coordinate.
	 * @param point_c_x Third point x-coordinate.
	 * @param point_c_y Third point y-coordinate.
	 * @param fill Whether to fill the triangle.
	 */
	CanvasDrawTriangleEvent::CanvasDrawTriangleEvent(unsigned long time, ColorCanvas* canvas, Colors::RGB color, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) : Event(time) {
		this->canvas_ = canvas;
		this->color_ = color;
		this->is_color_canvas_ = true;
		this->point_a_x_ = point_a_x;
		this->point_a_y_ = point_a_y;
		this->point_b_x_ = point_b_x;
		this->point_b_y_ = point_b_y;
		this->point_c_x_ = point_c_x;
		this->point_c_y_ = point_c_y;
		this->fill_ = fill;
	}

	void CanvasDrawTriangleEvent::run() {
		if (is_color_canvas_) {
			dynamic_cast<ColorCanvas*>(canvas_)->draw_triangle(color_, point_a_x_, point_a_y_, point_b_x_, point_b_y_, point_c_x_, point_c_y_, fill_);
		}
		else {
			canvas_->draw_triangle(point_a_x_, point_a_y_, point_b_x_, point_b_y_, point_c_x_, point_c_y_, fill_);
		}
	}
}
