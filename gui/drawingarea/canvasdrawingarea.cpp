/*
 * CanvasDrawingArea - Creates a Canvas for interacting directly with pixels.
 * Left mouse enables a pixel, right mouse disables a pixel, and Delete key clears the Canvas.
 */

#include "animation/solidanimation.h"
#include "canvasdrawingarea.h"
#include "QMouseEvent"
#include "QString"
#include "QToolTip"

CanvasDrawingArea::CanvasDrawingArea(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	// Enable mouse tracking
	this->setMouseTracking(true);

	// Create a simple 10 x 10 Canvas
	canvas_ = new Canvas(new bool[50 * 50] {0});

	maestro_controller->add_section_controller(new Point(50, 50));
	maestro_controller->get_section_controller(0)->get_section()->set_animation(new SolidAnimation());
	maestro_controller->get_section_controller(0)->set_colors(Colors::COLORWHEEL, 12);
	maestro_controller->get_section_controller(0)->get_section()->set_canvas(canvas_);
	maestro_controller->get_section_controller(0)->get_section()->get_animation()->set_fade(false);
}

bool CanvasDrawingArea::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type()==QEvent::KeyPress) {
		QKeyEvent* key = static_cast<QKeyEvent*>(event);
		if (key->key() == Qt::Key_Delete) {
			canvas_->clear();
		}
		else {
			return QObject::eventFilter(obj, event);
		}

		return true;
	}
	else {
		return QObject::eventFilter(obj, event);
	}

	return false;
}

void CanvasDrawingArea::mouseMoveEvent(QMouseEvent* event) {
	// Map cursor to row/column index
	cursor_->x = event->pos().x() / pad_;
	cursor_->y = event->pos().y() / pad_;

	/*
	 * If the left mouse button is held, enable the pixel.
	 * If the right mouse button is held, disable the pixel.
	 */
	if (event->buttons() == Qt::LeftButton) {
		canvas_->draw_point(cursor_);
	}
	else if (event->buttons() == Qt::RightButton) {
		canvas_->erase(cursor_);
	}
}

void CanvasDrawingArea::mousePressEvent(QMouseEvent* event) {
	this->mouseMoveEvent(event);
}
