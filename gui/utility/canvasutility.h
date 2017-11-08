/*
 * CanvasUtility - Tools for managing Canvases.
 */

#ifndef CANVASUTILITY_H
#define CANVASUTILITY_H

#include <QByteArray>
#include <QString>
#include "canvas/animationcanvas.h"
#include "canvas/canvas.h"
#include "canvas/colorcanvas.h"
#include "core/colors.h"
#include "widget/maestrocontrol.h"

using namespace PixelMaestro;

class CanvasUtility {
	public:
		static void copy_frameset(AnimationCanvas* canvas, bool** target, uint16_t target_x, uint16_t target_y, bool copy_from_canvas = true, MaestroControl* maestro_control = nullptr);
		static void copy_frameset(ColorCanvas* canvas, Colors::RGB** target, uint16_t target_x, uint16_t target_y, bool copy_from_canvas = true, MaestroControl* maestro_control = nullptr);
		static void load_image(QString filename, Canvas* canvas, MaestroControl* maestro_control = nullptr);
};

#endif // CANVASUTILITY_H
