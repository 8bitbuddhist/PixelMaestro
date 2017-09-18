/*
 * CanvasDrawingArea - Creates a Canvas for interacting directly with pixels.
 * Left mouse enables a pixel, right mouse disables a pixel, and Delete key clears the Canvas.
 *
 * IMPORTANT: Make sure to register the Canvas' eventFilter when adding it to the window.
 */

#ifndef CANVASDRAWINGAREA_H
#define CANVASDRAWINGAREA_H

#include "core/point.h"
#include "simpledrawingarea.h"

class CanvasDrawingArea : public SimpleDrawingArea {
	public:
		CanvasDrawingArea(QWidget* parent, MaestroController* maestro_controller, Canvas* canvas);
		~CanvasDrawingArea();

	protected:
		Canvas *canvas_ = nullptr;

		bool eventFilter(QObject *obj, QEvent *event);
		void mouseMoveEvent(QMouseEvent* event) override;
		void mousePressEvent(QMouseEvent* event) override;
};

#endif // CANVASDRAWINGAREA_H
