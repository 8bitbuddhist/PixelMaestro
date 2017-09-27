/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "showdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "drawingarea/simpledrawingarea.h"
#include <memory>
#include "show/show.h"

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(10, 10));

	SectionController *section_controller = maestro_controller_->get_section_controller(0);

	// TODO: Fix after Show revision
	/*
	 * Initialize Event.
	 * This show has just one Event, which simply changes to the next animation in the animations list every 5 seconds.
	 */
	//events_.push_back(new SectionSetAnimationEvent(5000, section_controller->get_section(), &animations_[0], animations_.size(), true));

	//Show* show = maestro_controller_->get_maestro()->add_show(&events_[0], events_.size());
	//show->set_timing(Show::TimingMode::Relative);
	//show->set_looping(true);
}
