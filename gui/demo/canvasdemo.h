/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */

#ifndef PATTERNDEMO_H
#define PATTERNDEMO_H

#include "../drawingarea/simpledrawingarea.h"
#include "controller/maestrocontroller.h"
#include <vector>

class CanvasDemo : public SimpleDrawingArea {
	public:
		CanvasDemo(QWidget* parent, MaestroController* maestro_controller);
};

#endif // PATTERNDEMO_H
