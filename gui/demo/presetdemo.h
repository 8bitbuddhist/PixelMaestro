/*
 * PresetDemo - Demonstrates using a preset to configure a Maestro.
 */

#ifndef PRESETDEMO_H
#define PRESETDEMO_H

#include "drawingarea/simpledrawingarea.h"
#include "controller/maestrocontroller.h"

class PresetDemo : public SimpleDrawingArea {
	public:
		PresetDemo(QWidget* parent, MaestroController* maestro_controller);
};

#endif // PRESETDEMO_H
