/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "command/animationcommand.h"
#include "command/sectioncommand.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "drawingarea/simpledrawingarea.h"
#include "show/runcommandevent.h"
#include <memory>
#include "showdemo.h"

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(10, 10));

	unsigned char *buffer = new unsigned char[100];

	// FIXME: This is just all effed up

	SectionCommand::set_animation(buffer, 0, Animation::Type::Wave, false, Colors::COLORWHEEL, 12);
	events_.push_back(new RunCommandEvent(5000, maestro_controller_->get_maestro(), buffer));

	/*
	SectionCommand::set_animation(buffer, 0, Animation::Type::Radial, true);
	events_.push_back(new RunCommandEvent(10000, maestro_controller_->get_maestro(), buffer));
	AnimationCommand::set_colors(buffer, 0, Colors::COLORWHEEL, 12);
	events_.push_back(new RunCommandEvent(0, maestro_controller_->get_maestro(), buffer));
	*/

	Show* show = maestro_controller_->get_maestro()->add_show(&events_[0], events_.size());
	show->set_timing(Show::TimingMode::Absolute);

	delete[] buffer;
}
