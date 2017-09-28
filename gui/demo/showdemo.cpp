/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "cue/animationcue.h"
#include "cue/sectioncue.h"
#include "cue/event.h"
#include "drawingarea/simpledrawingarea.h"
#include <memory>
#include "showdemo.h"

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	std::shared_ptr<SectionController> section_controller = maestro_controller_->add_section_controller(new Point(10, 10));

	CueController::Component handlers[] = {
		CueController::Component::AnimationComponent,
		CueController::Component::CanvasComponent,
		CueController::Component::SectionComponent
	};
	controller_ = new CueController(maestro_controller_->get_maestro(), handlers, 3);
	SectionCue* section_cue = static_cast<SectionCue*>(controller_->get_handler(CueController::Component::SectionComponent));
	AnimationCue* animation_cue = static_cast<AnimationCue*>(controller_->get_handler(CueController::Component::AnimationComponent));

	section_cue->set_animation(0, Animation::Type::Radial, false, Colors::COLORWHEEL, 12);
	controller_->run();

	Colors::RGB green_colors[16];
	Colors::generate_scaling_color_array(green_colors, &Colors::GREEN, &Colors::BLACK, 16, true);
	animation_cue->set_colors(0, green_colors, 16);
	unsigned char green_buffer[255];
	memcpy(green_buffer, controller_->get_buffer(), 255);

	Colors::RGB blue_colors[16];
	Colors::generate_scaling_color_array(blue_colors, &Colors::BLUE, &Colors::BLACK, 16, true);
	animation_cue->set_colors(0, blue_colors, 16);
	unsigned char blue_buffer[255];
	memcpy(blue_buffer, controller_->get_buffer(), 255);

	events_ = new Event[2] {
		Event(5000, maestro_controller_->get_maestro(), controller_, green_buffer),
		Event(5000, maestro_controller_->get_maestro(), controller_, blue_buffer)
	};

	Show* show = maestro_controller_->get_maestro()->add_show(events_, 2);
	show->set_timing(Show::TimingMode::Relative);
	show->set_looping(true);
}

ShowDemo::~ShowDemo() {
	delete controller_;
	delete[] events_;
}
