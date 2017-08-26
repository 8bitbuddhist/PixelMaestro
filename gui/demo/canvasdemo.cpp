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

	// Create a new Pixel grid 80 wide and 11 tall.
	Point *layout = new Point(80, 80);

	// Initializes our Canvas grid to thesame size of the Pixel grid. All values default to false.
	canvas_grid_ = new bool[layout->x * layout->y] {0};

	// Create the new Canvas.
	canvas_ = new Canvas(&canvas_grid_[0]);

	maestro_controller_ = maestroController;
	maestro_controller_->addSectionController(layout);

	SectionController *sectionController = maestro_controller_->getSectionController(0);
	std::shared_ptr<Section> section = sectionController->getSection();
	sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	section->setColorAnimation(Section::ColorAnimations::WAVE);
	section->setCanvas(canvas_);

	// Draw "Hello World!" and position it in the center of the Canvas.
	canvas_->drawText(new Point(10, 2), new Font5x8(), "Hello World!", 12);

	// Draw a border around the Canvas.
	//canvas_->drawRect(new Point(0, 0), new Point(80, 11), false);

	canvas_->drawTriangle(new Point(40, 10), new Point(80, 70), new Point(0, 70), false);

	canvas_->drawCircle(new Point(40, 40), 40, false);
	canvas_->drawCircle(new Point(40, 40), 30, false);
	canvas_->drawCircle(new Point(40, 40), 20, false);
	canvas_->drawCircle(new Point(40, 40), 10, true);
}
