/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */
#include "canvasdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include "canvas/fonts/font5x8.h"
#include "point.h"

CanvasDemo::CanvasDemo(QWidget *parent, MaestroController *maestroController) : SimpleDrawingArea(parent, maestro_controller_) {

	Point *layout = new Point(80, 8);

	pattern_array_ = new bool*[1] {
		new bool[layout->x * layout->y] {0}
	};

	canvas_ = new Canvas(pattern_array_, layout, 1);
	canvas_->drawText(new Font5x8(), 0, "Hello World!", 12);
	//canvas_->offset->x = 5;
	//canvas_->offset->y = 5;
	//canvas_->scrollRate = new Point(-1, 0);
	canvas_->repeat = true;

	maestro_controller_ = maestroController;
	maestro_controller_->addSectionController(layout);

	SectionController *sectionController = maestro_controller_->getSectionController(0);
	std::shared_ptr<Section> section = sectionController->getSection();
	sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	section->setColorAnimation(Section::ColorAnimations::WAVE);
	section->setCanvas(canvas_);
}
