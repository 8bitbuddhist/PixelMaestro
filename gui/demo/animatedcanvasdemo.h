/*
 * AnimatedCanvasDemo - Demonstrates animated Canvases using a GIF image.
 */

#ifndef ANIMATEDCANVASDEMO_H
#define ANIMATEDCANVASDEMO_H

#include <memory>
#include "controller/canvascontroller.h"
#include "controller/maestrocontroller.h"
#include "drawingarea/simpledrawingarea.h"

class AnimatedCanvasDemo : public SimpleDrawingArea {
	public:
		AnimatedCanvasDemo(QWidget* parent, MaestroController* maestro_controller);

	private:
		std::unique_ptr<CanvasController> canvas_controller_;
};

#endif // ANIMATEDCANVASDEMO_H
