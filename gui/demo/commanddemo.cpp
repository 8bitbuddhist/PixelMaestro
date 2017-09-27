#include "commanddemo.h"
#include "cue/animationcue.h"
#include "cue/cue.h"
#include "cue/canvascue.h"
#include "cue/sectioncue.h"

CommandDemo::CommandDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->add_section_controller(new Point(10, 10));

	unsigned char buffer[100] = {0};
	/*
	SectionCue::add_canvas(buffer, 0, CanvasType::ColorCanvas);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	CanvasCue::draw_circle(buffer, 0, Colors::GREEN, 5, 5, 2, true);
	Cue::run(maestro_controller_->get_maestro(), buffer);
	*/

	SectionCue::set_dimensions(buffer, 0, 100, 40);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	SectionCue::set_animation(buffer, 0, Animation::Type::Wave, false, Colors::COLORWHEEL, 12);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	AnimationCue::set_speed(buffer, 0, 1000, 750);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	SectionCue::add_canvas(buffer, 0, CanvasType::AnimationCanvas);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	CanvasCue::draw_text(buffer, 0, 0, 0, Font::Type::Font5x8, "Hello world!", 12);
	Cue::run(maestro_controller_->get_maestro(), buffer);
}

CommandDemo::~CommandDemo() {}
