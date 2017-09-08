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
	SectionController *sectionController = this->maestro_controller_->get_section_controller(0);

	std::shared_ptr<Section> section(sectionController->get_section());
	section->set_cycle_interval(500);

	Animation* blink_animation = new BlinkAnimation(section.get(), Colors::COLORWHEEL, 12);
	section->set_color_animation(blink_animation);
}
