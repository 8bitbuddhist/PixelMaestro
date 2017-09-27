/*
 * BlinkDemo - Displays a simple blink animation.
 */

#include "../drawingarea/simpledrawingarea.h"
#include "animation/blinkanimation.h"
#include "blinkdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/colors.h"
#include <memory>

BlinkDemo::BlinkDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(10, 10));
	SectionController *section_controller = this->maestro_controller_->get_section_controller(0);

	Section* section(section_controller->get_section());

	section->set_animation(new BlinkAnimation(Colors::COLORWHEEL, 12, 500));
}
