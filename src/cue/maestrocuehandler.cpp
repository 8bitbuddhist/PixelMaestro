#include "cuecontroller.h"
#include "maestrocuehandler.h"

namespace PixelMaestro {
	void MaestroCueHandler::set_refresh_interval(uint16_t interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_cue()[Byte::ActionByte] = Action::SetRefreshInterval;
		controller_->get_cue()[Byte::OptionsByte] = interval_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = interval_byte.converted_1;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 2));
	}

	void MaestroCueHandler::run(uint8_t *cue) {
		switch((Action)cue[MaestroCueHandler::Byte::ActionByte]) {
			case Action::SetRefreshInterval:
				{
					uint32_t interval = IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Byte::OptionsByte]);
					controller_->get_maestro()->set_refresh_interval(interval);
				}
				break;
		}
	}

	MaestroCueHandler::~MaestroCueHandler() { }
}
