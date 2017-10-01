/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "cue/animationcuehandler.h"
#include "cue/sectioncuehandler.h"
#include "cue/event.h"
#include "drawingarea/simpledrawingarea.h"
#include <memory>
#include "showdemo.h"

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(10, 10));

	CueController* controller = maestro_controller_->get_maestro()->add_cue_controller();

	SectionCueHandler* section_handler = static_cast<SectionCueHandler*>(controller->enable_handler(CueController::Handler::SectionHandler));
	AnimationCueHandler* animation_handler = static_cast<AnimationCueHandler*>(controller->enable_handler(CueController::Handler::AnimationHandler));

	section_handler->set_animation(0, 0, Animation::Type::Radial, false, Colors::COLORWHEEL, 12);
	controller->run();

	Colors::RGB green_colors[16];
	Colors::generate_scaling_color_array(green_colors, &Colors::GREEN, &Colors::BLACK, 16, true);
	animation_handler->set_colors(0, 0, green_colors, 16);
	unsigned char green_buffer[255];
	memcpy(green_buffer, controller->get_cue(), 255);

	Colors::RGB blue_colors[16];
	Colors::generate_scaling_color_array(blue_colors, &Colors::BLUE, &Colors::BLACK, 16, true);
	animation_handler->set_colors(0, 0, blue_colors, 16);
	unsigned char blue_buffer[255];
	memcpy(blue_buffer, controller->get_cue(), 255);

	events_ = new Event[2] {
		Event(5000, green_buffer),
		Event(5000, blue_buffer)
	};

	Show* show = maestro_controller_->get_maestro()->add_show(events_, 2);
	show->set_timing(Show::TimingMode::Relative);
	show->set_looping(true);
}

ShowDemo::~ShowDemo() {
	delete[] events_;
}
