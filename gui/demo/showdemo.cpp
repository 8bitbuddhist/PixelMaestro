/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "showdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"

ShowDemo::ShowDemo(QWidget *parent, MaestroController *maestroController) : SimpleDrawingArea(parent, this->maestro_controller_) {
	this->maestro_controller_ = maestroController;
	this->maestro_controller_->addSectionController();

	SectionController *sectionController = this->maestro_controller_->getSectionController(0);
	Section *section = sectionController->getSection();
	sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	section->setColorAnimation(Section::ColorAnimations::BLINK);
	section->setCycleInterval(300);

	// Initialize Transitions
	transitions_.resize(2);
	transitions_[0].time = 1000;
	transitions_[0].action = std::bind(&Section::toggleFade, section);

	transitions_[1].time = 1000;
	transitions_[1].action = std::bind(&Section::toggleFade, section);

	this->maestro_controller_->addShow(&transitions_[0], 2, Show::TimingModes::RELATIVE, true);

}
