/*
 * AnimatedCanvasDemo - Demonstrates animated Canvases using a GIF image.
 */

#ifndef ANIMATEDCANVASDEMO_H
#define ANIMATEDCANVASDEMO_H

#include <memory>
#include "controller/maestrocontroller.h"
#include "drawingarea/simpledrawingarea.h"

class AnimatedCanvasDemo : public SimpleDrawingArea {
	public:
		AnimatedCanvasDemo(QWidget* parent, MaestroController* maestro_controller);
};

#endif // ANIMATEDCANVASDEMO_H
