/*
 * CanvasUtility - Tools for managing Canvases.
 */

#ifndef CANVASUTILITY_H
#define CANVASUTILITY_H

#include <QByteArray>
#include <QString>
#include "canvas/canvas.h"
#include "widget/maestrocontrol.h"

using namespace PixelMaestro;

class CanvasUtility {
	public:
		static void load_image(QString filename, Canvas* canvas, MaestroControl* maestro_control = nullptr);
};

#endif // CANVASUTILITY_H
