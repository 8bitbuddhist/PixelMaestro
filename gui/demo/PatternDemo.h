/*
 * PatternDemo - Demonstrates a Maestro using a Show.
 */

#ifndef PATTERNDEMO_H
#define PATTERNDEMO_H

#include "controller/maestrocontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <vector>

class PatternDemo : public SimpleDrawingArea {
	public:
		PatternDemo(QWidget *parent, MaestroController *maestroController);
		bool *pattern_array_;

	private:
		Section::Pattern *pattern_;

};

#endif // PATTERNDEMO_H
