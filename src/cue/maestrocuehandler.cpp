#include "cuecontroller.h"
#include "maestrocuehandler.h"

namespace PixelMaestro {
	uint8_t* MaestroCueHandler::set_timing(uint16_t interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::SetTiming;
		controller_->get_buffer()[Byte::OptionsByte] = interval_byte.converted_0;
		controller_->get_buffer()[Byte::OptionsByte + 1] = interval_byte.converted_1;

		return controller_->assemble((Byte::OptionsByte + 2));
	}

	void MaestroCueHandler::run(uint8_t *cue) {
		switch((Action)cue[MaestroCueHandler::Byte::ActionByte]) {
			case Action::SetTiming:
				{
					uint32_t interval = IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Byte::OptionsByte]);
					controller_->get_maestro()->set_timing(interval);
				}
				break;
		}
	}

	MaestroCueHandler::~MaestroCueHandler() { }
}
