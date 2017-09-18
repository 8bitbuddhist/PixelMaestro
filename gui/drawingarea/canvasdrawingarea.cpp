/*
 * CanvasDrawingArea - Creates a Canvas for interacting directly with pixels.
 * Left mouse enables a pixel, right mouse disables a pixel, and Delete key clears the Canvas.
 */

#include "animation/solidanimation.h"
#include "canvasdrawingarea.h"
#include "QMouseEvent"
#include "QString"
#include "QToolTip"

CanvasDrawingArea::CanvasDrawingArea(QWidget* parent, MaestroController* maestro_controller, Canvas* canvas) : SimpleDrawingArea(parent, maestro_controller) {
	// Enable mouse tracking
	this->setMouseTracking(true);
	this->canvas_ = canvas;
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
	/*
	 * If the left mouse button is held, enable the pixel.
	 * If the right mouse button is held, disable the pixel.
	 */
	if (event->buttons() == Qt::LeftButton) {
		canvas_->draw_point(event->pos().x() / pad_, event->pos().y() / pad_);
	}
	else if (event->buttons() == Qt::RightButton) {
		canvas_->erase(event->pos().x() / pad_, event->pos().y() / pad_);
	}
}

void CanvasDrawingArea::mousePressEvent(QMouseEvent* event) {
	this->mouseMoveEvent(event);
}

CanvasDrawingArea::~CanvasDrawingArea() {
	this->setMouseTracking(false);
}
