/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */
#include "patterndemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include "pattern/fontutil.h"
#include "pattern/fonts/font5x8.h"

PatternDemo::PatternDemo(QWidget *parent, MaestroController *maestroController) : SimpleDrawingArea(parent, this->maestro_controller_) {

	Section::Layout *layout = new Section::Layout(8, 80);

	this->pattern_array_ = new bool*[1] {
		new bool[layout->getSize()] {0}
	};

	FontUtil::printString(new Font5x8(), this->pattern_array_[0], layout, "Hello World!", 12);

	this->pattern_ = new Section::Pattern(this->pattern_array_, layout, 1);
	//this->pattern_->offset->x = 5;
	//this->pattern_->offset->y = 5;
	this->pattern_->scrollRate = new Section::Coordinates(-1, 0);
	this->pattern_->repeat = true;

	this->maestro_controller_ = maestroController;
	this->maestro_controller_->addSectionController(layout);

	SectionController *sectionController = this->maestro_controller_->getSectionController(0);
	std::shared_ptr<Section> section = sectionController->getSection();
	sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	section->setColorAnimation(Section::ColorAnimations::PATTERN);
	section->setPattern(this->pattern_);
	section->toggleFade();
}
