/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#ifndef SHOWDEMO_H
#define SHOWDEMO_H

#include "../drawingarea/simpledrawingarea.h"
#include "controller/maestrocontroller.h"
#include <vector>

class ShowDemo : public SimpleDrawingArea {
	public:
		ShowDemo(QWidget* parent, MaestroController* maestro_controller);

	private:
		std::vector<Animation*> animations_;
		std::vector<Event*> events_;

};

#endif // SHOWDEMO_H
