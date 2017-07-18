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

		/// The size of each rendered Pixel.
		unsigned short RADIUS_ = 20;
		/// The amount of space between each Pixel.
		unsigned short PAD_ = RADIUS_ * 2;
		/// The offset of the grid from its initial starting point.
		unsigned short OFFSET_ = PAD_;
};

#endif // SIMPLEDRAWINGAREA_H
