#ifndef COMMANDDEMO_H
#define COMMANDDEMO_H

#include "controller/maestrocontroller.h"
#include "drawingarea/simpledrawingarea.h"

class CueDemo : public SimpleDrawingArea {
	public:
		CueDemo(QWidget* parent, MaestroController* maestro_controller);
		~CueDemo();
};

#endif // COMMANDDEMO_H
