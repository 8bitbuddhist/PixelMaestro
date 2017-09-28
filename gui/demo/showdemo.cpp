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

	int buffer_size = 100;
	unsigned char start_buffer[buffer_size];
	unsigned char green_buffer[buffer_size];
	unsigned char blue_buffer[buffer_size];

	// Start running an initial animation
	SectionCue::set_animation(start_buffer, 0, Animation::Type::Radial, false, Colors::COLORWHEEL, 12);
	Cue::run(maestro_controller_->get_maestro(), start_buffer);


	Colors::RGB green_colors[16];
	Colors::generate_scaling_color_array(green_colors, &Colors::GREEN, &Colors::BLACK, 16, true);
	AnimationCue::set_colors(green_buffer, 0, green_colors, 16);

	Colors::RGB blue_colors[16];
	Colors::generate_scaling_color_array(blue_colors, &Colors::GREEN, &Colors::BLACK, 16, true);
	AnimationCue::set_colors(blue_buffer, 0, blue_colors, 16);

	events_ = new Event[2] {
		Event(5000, maestro_controller_->get_maestro(), green_buffer),
		Event(5000, maestro_controller_->get_maestro(), blue_buffer)
	};

	Show* show = maestro_controller_->get_maestro()->add_show(events_, 2);
	show->set_timing(Show::TimingMode::Relative);
	show->set_looping(true);
}

ShowDemo::~ShowDemo() {
	delete[] events_;
}
