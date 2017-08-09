/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#ifndef SHOWDEMO_H
#define SHOWDEMO_H

#include "controller/maestrocontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <vector>

class ShowDemo : public SimpleDrawingArea {
	public:
		ShowDemo(QWidget *parent, MaestroController *maestroController);
		std::vector<Show::Transition> transitions_;

};

#endif // SHOWDEMO_H
