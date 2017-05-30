#ifndef SIMPLEDRAWINGAREA_H
#define SIMPLEDRAWINGAREA_H

#include "controller/maestrocontroller.h"
#include "maestrodrawingarea.h"

class SimpleDrawingArea : public MaestroDrawingArea {
	public:
		SimpleDrawingArea(QWidget *parent, MaestroController *maestroController);

	protected:
		void paintEvent(QPaintEvent *event) override;

		// Window/drawing area variables
		static const unsigned short RADIUS_ = 20;
		static const unsigned short PAD_ = RADIUS_ * 2;
		static const unsigned short OFFSET_ = RADIUS_ * 2;
};

#endif // SIMPLEDRAWINGAREA_H
