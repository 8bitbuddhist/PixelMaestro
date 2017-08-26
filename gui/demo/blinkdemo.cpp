/*
 * BlinkDemo - Displays a simple blink animation.
 */

#include "blinkdemo.h"
#include "colors.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <memory>

BlinkDemo::BlinkDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, this->maestro_controller_) {
	this->maestro_controller_ = maestro_controller;

	this->maestro_controller_->add_section_controller(new Point(10, 10));
	SectionController *sectionController = this->maestro_controller_->get_section_controller(0);

	sectionController->set_controller_colors(Colors::COLORWHEEL, 12);

	std::shared_ptr<Section> section(sectionController->get_section());
	section->set_color_animation(Section::ColorAnimations::BLINK, true, Section::AnimationOrientations::HORIZONTAL);
	section->set_cycle_interval(500);
}
