/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "showdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <memory>
#include "../src/show/SectionSetColorAnimationEvent.h"

ShowDemo::ShowDemo(QWidget *parent, MaestroController *maestroController) : SimpleDrawingArea(parent, this->maestro_controller_) {
	this->maestro_controller_ = maestroController;
	this->maestro_controller_->addSectionController(new Section::Layout(10, 10));

	SectionController *sectionController = this->maestro_controller_->getSectionController(0);
	std::shared_ptr<Section> section = sectionController->getSection();
	sectionController->setControllerColors(Colors::COLORWHEEL, 12);
	section->setColorAnimation(Section::ColorAnimations::SOLID);
	section->setCycleInterval(300);

	/*
	 * Initialize Event.
	 * This show has just one Event, which simply changes to the next animation every 5 seconds.
	 */
	events_.push_back(new SectionSetColorAnimationEvent(5000, section.get(), Section::ColorAnimations::NEXT, false, Section::AnimationOrientations::HORIZONTAL));

	this->maestro_controller_->addShow(&events_[0], events_.size(), Show::TimingModes::RELATIVE, true);

}
