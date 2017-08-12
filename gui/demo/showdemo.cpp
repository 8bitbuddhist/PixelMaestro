/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "showdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include "../src/show/SectionSetColorAnimationTransition.h"

ShowDemo::ShowDemo(QWidget *parent, MaestroController *maestroController) : SimpleDrawingArea(parent, this->maestro_controller_) {
	this->maestro_controller_ = maestroController;
	this->maestro_controller_->addSectionController();

	SectionController *sectionController = this->maestro_controller_->getSectionController(0);
	Section *section = sectionController->getSection();
	sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	section->setColorAnimation(Section::ColorAnimations::SOLID);
	section->setCycleInterval(300);

	/*
	 * Initialize Transition.
	 * This show has just one Transition, which simply changes to the next animation every 5 seconds.
	 */
	transitions_.push_back(new SectionSetColorAnimationTransition(section, 5000, Section::ColorAnimations::NEXT, false, Section::AnimationOrientations::HORIZONTAL));

	this->maestro_controller_->addShow(&transitions_[0], transitions_.size(), Show::TimingModes::RELATIVE, true);

}
