/*
 * BlinkDemo - Displays a simple blink animation.
 */

#ifndef BLINKDEMO_H
#define BLINKDEMO_H

#include "controller/maestrocontroller.h"
#include "../drawingarea/simpledrawingarea.h"

class BlinkDemo : public SimpleDrawingArea {
	public:
		BlinkDemo(QWidget *parent, MaestroController *maestroController);
};

#endif // BLINKDEMO_H
