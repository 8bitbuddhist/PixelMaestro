#include "commanddemo.h"
#include "serial/command.h"

CommandDemo::CommandDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	unsigned int args[] = {90};
	Command command = Command(Command::Action::MaestroChangeRefreshInterval, args);
	Command::run(maestro_controller_->get_maestro(), command.get_command());
}

CommandDemo::~CommandDemo() {}
