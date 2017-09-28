#include "cuedemo.h"
#include "cue/animationcue.h"
#include "cue/cue.h"
#include "cue/canvascue.h"
#include "cue/sectioncue.h"

CueDemo::CueDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->add_section_controller(new Point(10, 10));

	Maestro* maestro = maestro_controller_->get_maestro();

	unsigned char buffer[100] = {0};

	SectionCue::add_overlay(buffer, 0, Colors::MixMode::Overlay, 0);
	Cue::run(maestro, buffer);

	SectionCue::set_dimensions(buffer, 0, 62, 10);
	Cue::run(maestro, buffer);

	Colors::RGB colors[] = {Colors::SPRING, Colors::ROSE};
	SectionCue::set_animation(buffer, 0, Animation::Type::Cycle, false, colors, 2);
	Cue::run(maestro, buffer);

	AnimationCue::set_speed(buffer, 0, 1000, 750);
	Cue::run(maestro, buffer);

	SectionCue::add_canvas(buffer, 0, CanvasType::AnimationCanvas);
	Cue::run(maestro, buffer);

	CanvasCue::draw_text(buffer, 0, 1, 1, Font::Type::Font5x8, "Hello world!", 12);
	Cue::run(maestro, buffer);

}

CueDemo::~CueDemo() {}
