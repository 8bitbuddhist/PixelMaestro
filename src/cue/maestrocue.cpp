#include "cuecontroller.h"
#include "maestrocuehandler.h"

namespace PixelMaestro {
	void MaestroCueHandler::set_refresh_interval(unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::MaestroHandler;
		controller_->get_cue()[Bit::ActionBit] = Action::SetRefreshInterval;
		controller_->get_cue()[Bit::OptionsBit] = interval_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = interval_byte.converted_1;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 2));
	}

	void MaestroCueHandler::run(unsigned char *cue) {
		switch((Action)cue[MaestroCueHandler::Bit::ActionBit]) {
			case Action::SetRefreshInterval:
				{
					unsigned int interval = IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Bit::OptionsBit]);
					controller_->get_maestro()->set_refresh_interval(interval);
				}
				break;
		}
	}
}
