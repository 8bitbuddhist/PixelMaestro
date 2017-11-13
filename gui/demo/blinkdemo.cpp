/*
 * BlinkDemo - Displays a simple blink animation.
 */

#include "blinkdemo.h"
#include "colorpresets.h"
#include "controller/maestrocontroller.h"
#include "core/colors.h"
#include "drawingarea/simpledrawingarea.h"

BlinkDemo::BlinkDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	Section* section = maestro_controller_->set_sections(1, Point(10, 10));

	Animation* animation = section->set_animation(AnimationType::Blink, ColorPresets::COLORWHEEL, 12);
	animation->set_speed(1000);
}
