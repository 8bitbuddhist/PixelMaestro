#include "commanddemo.h"
#include "serial/serial.h"
#include "serial/sectionserial.h"
#include "serial/canvasserial.h"

CommandDemo::CommandDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->add_section_controller(new Point(10, 10));

	unsigned char buffer[100] = {0};
	SectionSerial::add_canvas(buffer, 0, CanvasType::ColorCanvas);
	Serial::run(maestro_controller_->get_maestro(), buffer);

	CanvasSerial::draw_circle(buffer, 0, Colors::GREEN, 5, 5, 2, true);
	Serial::run(maestro_controller_->get_maestro(), buffer);
}

CommandDemo::~CommandDemo() {}
