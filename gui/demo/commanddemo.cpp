#include "commanddemo.h"
#include "serial/animationserial.h"
#include "serial/serial.h"
#include "serial/canvasserial.h"
#include "serial/sectionserial.h"

CommandDemo::CommandDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->add_section_controller(new Point(10, 10));

	unsigned char buffer[100] = {0};
	/*
	SectionSerial::add_canvas(buffer, 0, CanvasType::ColorCanvas);
	Serial::run(maestro_controller_->get_maestro(), buffer);

	CanvasSerial::draw_circle(buffer, 0, Colors::GREEN, 5, 5, 2, true);
	Serial::run(maestro_controller_->get_maestro(), buffer);
	*/

	SectionSerial::set_animation(buffer, 0, Animation::Type::Wave, false);
	Serial::run(maestro_controller_->get_maestro(), buffer);

	AnimationSerial::set_colors(buffer, 0, Colors::COLORWHEEL, 12);
	Serial::run(maestro_controller_->get_maestro(), buffer);

	AnimationSerial::set_speed(buffer, 0, 1000, 750);
	Serial::run(maestro_controller_->get_maestro(), buffer);
}

CommandDemo::~CommandDemo() {}
