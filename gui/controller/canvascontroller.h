/*
 * CanvasController - Wrapper class for managing Canvases.
 */

#ifndef CANVASCONTROLLER_H
#define CANVASCONTROLLER_H

#include <QByteArray>
#include <QString>
#include "canvas/canvas.h"
#include "controller/sectioncontroller.h"
#include "core/section.h"
#include "widget/maestrocontrol.h"

class MaestroControl;

class CanvasController {
	public:
		CanvasController(SectionController* section_controller, CanvasType::Type canvas_type, uint16_t num_frames = 1);
		CanvasController(SectionController* section_controller, MaestroControl* maestro_control, CanvasType::Type canvas_type, uint16_t num_frames = 1);
		~CanvasController();
		Canvas* get_canvas();
		void load_image(QString filename, QByteArray filetype);

	private:
		Canvas* canvas_ = nullptr;
		MaestroControl* maestro_control_ = nullptr;
		SectionController* section_controller_ = nullptr;
};

#endif // CANVASCONTROLLER_H
