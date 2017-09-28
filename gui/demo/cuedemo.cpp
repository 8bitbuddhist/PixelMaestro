#include "cuedemo.h"
#include "cue/animationcue.h"
#include "cue/cuecontroller.h"
#include "cue/canvascue.h"
#include "cue/sectioncue.h"

CueDemo::CueDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->add_section_controller(new Point(10, 10));

	Maestro* maestro = maestro_controller_->get_maestro();

	CueController::Component handlers[] = {
		CueController::Component::AnimationComponent,
		CueController::Component::CanvasComponent,
		CueController::Component::SectionComponent
	};
	CueController controller(maestro, handlers, 3);

	SectionCue *section_handler = static_cast<SectionCue*>(controller.get_handler(CueController::Component::SectionComponent));
	section_handler->add_overlay(0, Colors::MixMode::Overlay, 0);
	controller.run();

	section_handler->set_dimensions(0, 62, 10);
	controller.run();

	Colors::RGB colors[] = {Colors::SPRING, Colors::ROSE};
	section_handler->set_animation(0, Animation::Type::Cycle, false, colors, 2);
	controller.run();

	AnimationCue* animation_handler = static_cast<AnimationCue*>(controller.get_handler(CueController::Component::AnimationComponent));
	animation_handler->set_speed(0, 1000, 750);
	controller.run();

	section_handler->add_canvas(0, CanvasType::AnimationCanvas);
	controller.run();

	CanvasCue* canvas_handler = static_cast<CanvasCue*>(controller.get_handler(CueController::Component::CanvasComponent));
	canvas_handler->draw_text(0, 1, 1, Font::Type::Font5x8, "Hello world!", 12);
	controller.run();
}

CueDemo::~CueDemo() {}
