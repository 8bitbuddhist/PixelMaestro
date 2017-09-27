#include "cuedemo.h"
#include "cue/animationcue.h"
#include "cue/cue.h"
#include "cue/canvascue.h"
#include "cue/sectioncue.h"

CueDemo::CueDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->add_section_controller(new Point(10, 10));

	unsigned char buffer[100] = {0};

	SectionCue::set_dimensions(buffer, 0, 62, 10);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	Colors::RGB black_white[] = {Colors::WHITE, Colors::BLACK};
	SectionCue::set_animation(buffer, 0, Animation::Type::Wave, false, black_white, 2);
	//SectionCue::set_animation(buffer, 0, Animation::Type::Blink, false, Colors::COLORWHEEL, 2);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	AnimationCue::set_speed(buffer, 0, 1000, 750);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	SectionCue::add_canvas(buffer, 0, CanvasType::AnimationCanvas);
	Cue::run(maestro_controller_->get_maestro(), buffer);

	CanvasCue::draw_text(buffer, 0, 1, 1, Font::Type::Font5x8, "Hello world!", 12);
	Cue::run(maestro_controller_->get_maestro(), buffer);
}

CueDemo::~CueDemo() {}
