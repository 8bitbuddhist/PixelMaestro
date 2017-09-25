#include "commanddemo.h"
#include "serial/command.h"

CommandDemo::CommandDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	//unsigned int args[] = {90};
	//Command command = Command(Command::Action::MaestroChangeRefreshInterval, args);


	unsigned int args[] = {0, CanvasType::AnimationCanvas};
	Command command = Command(Command::Action::SectionAddCanvas, args);
	maestro_controller_->add_section_controller(new Point(10, 10));


	Command::run(maestro_controller_->get_maestro(), command.get_command());
}

CommandDemo::~CommandDemo() {}
