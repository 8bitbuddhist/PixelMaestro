#ifndef COLORCANVASDEMO_H
#define COLORCANVASDEMO_H

#include "controller/maestrocontroller.h"
#include "drawingarea/simpledrawingarea.h"

class ColorCanvasDemo : public SimpleDrawingArea {
	public:
		ColorCanvasDemo(QWidget* parent, MaestroController* maestro_controller);
};

#endif // COLORCANVASDEMO_H
