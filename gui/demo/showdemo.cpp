/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "colorpresets.h"
#include "controller/maestrocontroller.h"
#include "cue/animationcuehandler.h"
#include "cue/canvascuehandler.h"
#include "cue/sectioncuehandler.h"
#include "cue/event.h"
#include "drawingarea/simpledrawingarea.h"
#include <memory>
#include "showdemo.h"

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->set_sections(1, Point(25, 10));

	CueController* controller = maestro_controller_->get_maestro()->set_cue_controller();

	SectionCueHandler* section_handler = static_cast<SectionCueHandler*>(controller->enable_handler(CueController::Handler::SectionHandler));
	AnimationCueHandler* animation_handler = static_cast<AnimationCueHandler*>(controller->enable_handler(CueController::Handler::AnimationHandler));
	CanvasCueHandler* canvas_handler = static_cast<CanvasCueHandler*>(controller->enable_handler(CueController::Handler::CanvasHandler));

	controller->run(section_handler->set_animation(0, 0, AnimationType::Type::Wave, false, ColorPresets::COLORWHEEL, 12));
	controller->run(animation_handler->set_speed(0, 0, 500));
	controller->run(section_handler->set_canvas(0, 0, CanvasType::Type::AnimationCanvas));

	events_ = new Event[5];

	std::string text[] = {"1", "2", "3", "4"};
	for (uint8_t i = 0; i < 4; i++) {
		events_[i].set_cue(canvas_handler->draw_text(0, 0, i * 6, 1, Font::Type::Font5x8, text[i].c_str(), 1));
		events_[i].set_time(1000);
	}

	events_[4].set_cue(canvas_handler->clear(0, 0));
	events_[4].set_time(1000);

	Show* show = maestro_controller_->get_maestro()->set_show(events_, 5);
	show->set_timing(Show::TimingMode::Relative);
	show->set_looping(true);
}

ShowDemo::~ShowDemo() {
	delete[] events_;
}
