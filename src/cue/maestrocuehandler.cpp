#include "cuecontroller.h"
#include "maestrocuehandler.h"

namespace PixelMaestro {
	void MaestroCueHandler::set_refresh_interval(unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		controller_->get_cue()[Byte::HandlerByte] = (unsigned char)CueController::Handler::MaestroHandler;
		controller_->get_cue()[Byte::ActionByte] = Action::SetRefreshInterval;
		controller_->get_cue()[Byte::OptionsByte] = interval_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = interval_byte.converted_1;

		controller_->assemble((unsigned char)(Byte::OptionsByte + 2));
	}

	void MaestroCueHandler::run(unsigned char *cue) {
		switch((Action)cue[MaestroCueHandler::Byte::ActionByte]) {
			case Action::SetRefreshInterval:
				{
					unsigned int interval = IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Byte::OptionsByte]);
					controller_->get_maestro()->set_refresh_interval(interval);
				}
				break;
		}
	}

	MaestroCueHandler::~MaestroCueHandler() { }
}
