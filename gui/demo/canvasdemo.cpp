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

	Point *layout = new Point(80, 10);

	pattern_array_ = new bool[layout->x * layout->y] {0};

	canvas_ = new Canvas(&pattern_array_[0], layout);
	canvas_->bg_color = &Colors::WHITE;
	canvas_->drawText(new Point(5, 2), new Font5x8(),"Hello World!", 12);
	//canvas_->offset->x = 5;
	//canvas_->offset->y = 5;
	//canvas_->scroll_interval = new Point(0, 1);
	canvas_->repeat = true;

	maestro_controller_ = maestroController;
	maestro_controller_->addSectionController(layout);

	SectionController *sectionController = maestro_controller_->getSectionController(0);
	std::shared_ptr<Section> section = sectionController->getSection();
	//sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	sectionController->setControllerColors(new Colors::RGB {Colors::BLACK}, 1);
	section->setColorAnimation(Section::ColorAnimations::SOLID);
	section->setCanvas(canvas_);
	section->toggleFade();
}
