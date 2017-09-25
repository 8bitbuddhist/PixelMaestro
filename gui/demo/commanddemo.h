#ifndef COMMANDDEMO_H
#define COMMANDDEMO_H

#include "controller/maestrocontroller.h"
#include "drawingarea/simpledrawingarea.h"

class CommandDemo : public SimpleDrawingArea {
	public:
		CommandDemo(QWidget* parent, MaestroController* maestro_controller);
		~CommandDemo();
};

#endif // COMMANDDEMO_H
