/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */
#include "patterndemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"

PatternDemo::PatternDemo(QWidget *parent, MaestroController *maestroController) : SimpleDrawingArea(parent, this->maestro_controller_) {
	/*
	 * Create a new Pattern showing a square converging into the center of the grid.
	 * This Pattern is five frames long, with each frame reducing the size of the square by 1 Pixel.
	 */
	this->pattern_array_ = new bool*[5] {
		// Frame 1: Border
		new bool[100] {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		},

		// Frame 2: Inner circle
		new bool[100] {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
			0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		},

		// Frame 3
		new bool[100] {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		},

		// Frame 4
		new bool[100] {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
			0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
			0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		},

		// Frame 5
		new bool[100] {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
			0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		}
	};

	this->pattern_ = new Section::Pattern(this->pattern_array_, new Section::Layout(10, 10), 5);
	//this->pattern_->offset->x = 5;
	//this->pattern_->offset->y = 5;
	//this->pattern_->scrollRate = new Section::Offset(1, 1);
	//this->pattern_->repeat = true;

	this->maestro_controller_ = maestroController;
	this->maestro_controller_->addSectionController(new Section::Layout(10, 10));

	SectionController *sectionController = this->maestro_controller_->getSectionController(0);
	std::shared_ptr<Section> section = sectionController->getSection();
	sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	section->setColorAnimation(Section::ColorAnimations::PATTERN);
	section->setPattern(this->pattern_);
}
