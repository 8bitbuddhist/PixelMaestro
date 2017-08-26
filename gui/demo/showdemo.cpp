/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "showdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <memory>
#include "../src/show/sectionsetcoloranimationevent.h"

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, this->maestro_controller_) {
	this->maestro_controller_ = maestro_controller;
	this->maestro_controller_->add_section_controller(new Point(10, 10));

	SectionController *sectionController = this->maestro_controller_->get_section_controller(0);
	std::shared_ptr<Section> section = sectionController->get_section();
	sectionController->set_controller_colors(Colors::COLORWHEEL, 12);
	section->set_color_animation(Section::ColorAnimations::SOLID);
	section->set_cycle_interval(300);

	/*
	 * Initialize Event.
	 * This show has just one Event, which simply changes to the next animation every 5 seconds.
	 */
	events_.push_back(new SectionSetColorAnimationEvent(5000, section.get(), Section::ColorAnimations::NEXT, false, Section::AnimationOrientations::HORIZONTAL));

	this->maestro_controller_->add_show(&events_[0], events_.size(), Show::TimingModes::RELATIVE, true);

}
