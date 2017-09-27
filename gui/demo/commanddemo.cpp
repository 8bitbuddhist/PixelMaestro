#include "commanddemo.h"
#include "command/animationcommand.h"
#include "command/command.h"
#include "command/canvascommand.h"
#include "command/sectioncommand.h"

CommandDemo::CommandDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_->add_section_controller(new Point(10, 10));

	unsigned char buffer[100] = {0};
	/*
	SectionCommand::add_canvas(buffer, 0, CanvasType::ColorCanvas);
	Command::run(maestro_controller_->get_maestro(), buffer);

	CanvasCommand::draw_circle(buffer, 0, Colors::GREEN, 5, 5, 2, true);
	Command::run(maestro_controller_->get_maestro(), buffer);
	*/

	SectionCommand::set_dimensions(buffer, 0, 100, 40);
	Command::run(maestro_controller_->get_maestro(), buffer);

	SectionCommand::set_animation(buffer, 0, Animation::Type::Wave, false, Colors::COLORWHEEL, 12);
	Command::run(maestro_controller_->get_maestro(), buffer);

	AnimationCommand::set_speed(buffer, 0, 1000, 750);
	Command::run(maestro_controller_->get_maestro(), buffer);

	SectionCommand::add_canvas(buffer, 0, CanvasType::AnimationCanvas);
	Command::run(maestro_controller_->get_maestro(), buffer);

	CanvasCommand::draw_text(buffer, 0, 0, 0, Font::Type::Font5x8, "Hello world!", 12);
	Command::run(maestro_controller_->get_maestro(), buffer);
}

CommandDemo::~CommandDemo() {}
