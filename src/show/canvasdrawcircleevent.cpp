#include "canvasdrawcircleevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a circle on a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param origin_x Center x coordinate.
	 * @param origin_y Center y coordinate.
	 * @param radius The size of the circle.
	 * @param fill Whether or not to fill the circle.
	 */
	CanvasDrawCircleEvent::CanvasDrawCircleEvent(unsigned long time, Canvas* canvas, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) : Event(time) {
		this->canvas_ = canvas;
		this->origin_x_ = origin_x;
		this->origin_y_ = origin_y;
		this->radius_ = radius;
		this->fill_ = fill;
	}

	/**
	 * Constructor. Draws a circle on a ColorCanvas.
	 * @param time Time until the Event runs.
	 * @param canvas ColorCanvas to draw on.
	 * @param color The color to use while drawing.
	 * @param origin_x Center x coordinate.
	 * @param origin_y Center y coordinate.
	 * @param radius The size of the circle.
	 * @param fill Whether or not to fill the circle.
	 */
	CanvasDrawCircleEvent::CanvasDrawCircleEvent(unsigned long time, ColorCanvas* canvas, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) : Event(time) {
		this->color_ = color;
		this->is_color_canvas_ = true;
		this->canvas_ = canvas;
		this->origin_x_ = origin_x;
		this->origin_y_ = origin_y;
		this->radius_ = radius;
		this->fill_ = fill;
	}

	void CanvasDrawCircleEvent::run() {
		if (is_color_canvas_) {
			static_cast<ColorCanvas*>(canvas_)->draw_circle(color_, origin_x_, origin_y_, radius_, fill_);
		}
		else {
			canvas_->draw_circle(origin_x_, origin_y_, radius_, fill_);
		}
	}
}
