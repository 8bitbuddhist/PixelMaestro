/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */

#ifndef PATTERNDEMO_H
#define PATTERNDEMO_H

#include "controller/maestrocontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <vector>

class CanvasDemo : public SimpleDrawingArea {
	public:
		CanvasDemo(QWidget *parent, MaestroController *maestroController);

	private:
		Canvas *canvas_;
		bool **pattern_array_;

};

#endif // PATTERNDEMO_H
