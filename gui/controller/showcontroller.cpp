#include "maestrocontroller.h"
#include "Show.h"
#include "showcontroller.h"

using namespace PixelMaestro;

ShowController::ShowController(MaestroController *maestro) {
	this->maestro_ = maestro;
	this->show_.setMaestro(this->maestro_->getMaestro());
}
