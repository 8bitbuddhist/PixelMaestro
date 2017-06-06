#ifndef SIMPLEDRAWINGAREA_H
#define SIMPLEDRAWINGAREA_H

#include "controller/maestrocontroller.h"
#include "maestrodrawingarea.h"

class SimpleDrawingArea : public MaestroDrawingArea {
	public:
		SimpleDrawingArea(QWidget *parent, MaestroController *maestroController);
		void resizePixels();

	protected:
		void paintEvent(QPaintEvent *event) override;

		// Window/drawing area variables
		unsigned short RADIUS_ = 20;
		unsigned short PAD_ = RADIUS_ * 2;
		unsigned short OFFSET_ = RADIUS_ * 2;
};

#endif // SIMPLEDRAWINGAREA_H
