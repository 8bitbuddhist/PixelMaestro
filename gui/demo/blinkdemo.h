#ifndef BLINKDEMO_H
#define BLINKDEMO_H

#include "Maestro.h"
#include "../drawingarea/simpledrawingarea.h"

class BlinkDemo : public SimpleDrawingArea {
	public:
		BlinkDemo(QWidget *parent);
		Maestro maestro_;
};

#endif // BLINKDEMO_H
