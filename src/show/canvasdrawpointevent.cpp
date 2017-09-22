#include "canvasdrawpointevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Draws a single point on a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to draw on.
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 */
	CanvasDrawPointEvent::CanvasDrawPointEvent(unsigned long time, BaseCanvas *canvas, unsigned short cursor_x, unsigned short cursor_y) : Event(time) {
		this->canvas_ = canvas;
		this->cursor_x_ = cursor_x;
		this->cursor_y_ = cursor_y;
	}

	/**
	 * Constructor. Draws a single point on a ColorCanvas.
	 * @param time Time until the Event runs.
	 * @param canvas ColorCanvas to draw on.
	 * @param color Color to draw in.
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 */
	CanvasDrawPointEvent::CanvasDrawPointEvent(unsigned long time, ColorCanvas *canvas, Colors::RGB color, unsigned short cursor_x, unsigned short cursor_y) : Event(time) {
		this->canvas_ = canvas;
		this->color_ = color;
		this->is_color_canvas_ = true;
		this->cursor_x_ = cursor_x;
		this->cursor_y_ = cursor_y;
	}

	void CanvasDrawPointEvent::run() {
		if (is_color_canvas_) {
			dynamic_cast<ColorCanvas*>(canvas_)->draw_point(color_, cursor_x_, cursor_y_);
		}
		else {
			canvas_->draw_point(cursor_x_, cursor_y_);
		}
	}
}
