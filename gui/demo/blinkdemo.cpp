/*
 * BlinkDemo - Displays a simple blink animation.
 */

#include "blinkdemo.h"
#include "Colors.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <memory>

BlinkDemo::BlinkDemo(QWidget *parent, MaestroController *maestroController) : SimpleDrawingArea(parent, this->maestro_controller_) {
	this->maestro_controller_ = maestroController;

	this->maestro_controller_->addSectionController();
	SectionController *sectionController = this->maestro_controller_->getSectionController(0);

	sectionController->setControllerColors(Colors::COLORWHEEL, 12);

	std::shared_ptr<Section> section(sectionController->getSection());
	section->setColorAnimation(Section::ColorAnimations::BLINK, true, Section::AnimationOrientations::HORIZONTAL);
	section->setCycleInterval(500);
}
