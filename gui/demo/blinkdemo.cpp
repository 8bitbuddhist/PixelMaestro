/*
 * BlinkDemo - Displays a simple blink animation.
 */

#include "blinkdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/colors.h"
#include "drawingarea/simpledrawingarea.h"

BlinkDemo::BlinkDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(10, 10));
	SectionController *section_controller = this->maestro_controller_->get_section_controller(0);

	Section* section(section_controller->get_section());
	Animation* animation = section->add_animation(AnimationType::Blink, Colors::COLORWHEEL, 12);
	animation->set_speed(500);
}
