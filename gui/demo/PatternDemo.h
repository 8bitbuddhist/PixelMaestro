/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */

#ifndef PATTERNDEMO_H
#define PATTERNDEMO_H

#include "controller/maestrocontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <vector>

class PatternDemo : public SimpleDrawingArea {
	public:
		PatternDemo(QWidget *parent, MaestroController *maestroController);

	private:
		Section::Pattern *pattern_;
		bool **pattern_array_;

};

#endif // PATTERNDEMO_H
