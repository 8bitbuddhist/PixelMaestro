/*
 * BlinkDemo - Displays a simple blink animation.
 */

#ifndef BLINKDEMO_H
#define BLINKDEMO_H

#include "../drawingarea/simpledrawingarea.h"
#include "controller/maestrocontroller.h"

class BlinkDemo : public SimpleDrawingArea {
	public:
		BlinkDemo(QWidget* parent, MaestroController* maestro_controller);
};

#endif // BLINKDEMO_H
