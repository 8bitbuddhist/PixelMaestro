#ifndef SIMPLEDRAWINGAREA_H
#define SIMPLEDRAWINGAREA_H

#include "maestrodrawingarea.h"

class SimpleDrawingArea : public MaestroDrawingArea {
	public:
		SimpleDrawingArea(QWidget *parent, Maestro *maestro);
		SimpleDrawingArea(QWidget *parent, Maestro *maestro, unsigned short rows, unsigned short columns);

	protected:
		void paintEvent(QPaintEvent *event) override;

		// Window/drawing area variables
		static const unsigned short RADIUS_ = 20;
		static const unsigned short PAD_ = RADIUS_ * 2;
		static const unsigned short OFFSET_ = RADIUS_ * 2;
};

#endif // SIMPLEDRAWINGAREA_H
