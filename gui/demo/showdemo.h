/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#ifndef SHOWDEMO_H
#define SHOWDEMO_H

#include "../drawingarea/simpledrawingarea.h"
#include "controller/maestrocontroller.h"

class ShowDemo : public SimpleDrawingArea {
	public:
		ShowDemo(QWidget* parent, MaestroController* maestro_controller);
		~ShowDemo();

	private:
		Event* events_;

};

#endif // SHOWDEMO_H
