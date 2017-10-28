/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */

#ifndef PATTERNDEMO_H
#define PATTERNDEMO_H

#include "controller/maestrocontroller.h"
#include "drawingarea/simpledrawingarea.h"

class CanvasDemo : public SimpleDrawingArea {
	public:
		CanvasDemo(QWidget* parent, MaestroController* maestro_controller);
};

#endif // PATTERNDEMO_H
