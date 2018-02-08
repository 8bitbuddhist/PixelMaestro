#include "cuecontroller.h"
#include "maestrocuehandler.h"
#include "showcuehandler.h"

namespace PixelMaestro {
	uint8_t* MaestroCueHandler::set_show() {
		// Note: This only initializes the Show. You still need to set Events using ShowCueHandler::set_events().
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::SetShow;

		return controller_->assemble(Byte::OptionsByte);
	}

	uint8_t* MaestroCueHandler::set_timer(uint16_t interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::SetTimer;
		controller_->get_buffer()[Byte::OptionsByte] = interval_byte.converted_0;
		controller_->get_buffer()[Byte::OptionsByte + 1] = interval_byte.converted_1;

		return controller_->assemble((Byte::OptionsByte + 2));
	}

	uint8_t* MaestroCueHandler::start() {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::Start;

		return controller_->assemble(Byte::OptionsByte);
	}

	uint8_t* MaestroCueHandler::stop() {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::Stop;

		return controller_->assemble(Byte::OptionsByte);
	}

	uint8_t* MaestroCueHandler::sync(const uint32_t new_time) {
		IntByteConvert last_time_byte(new_time);

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::MaestroHandler;
		controller_->get_buffer()[Byte::ActionByte] = Action::Sync;
		controller_->get_buffer()[Byte::OptionsByte] = last_time_byte.converted_0;
		controller_->get_buffer()[Byte::OptionsByte + 1] = last_time_byte.converted_1;

		return controller_->assemble((Byte::OptionsByte + 2));
	}

	void MaestroCueHandler::run(uint8_t *cue) {
		Maestro* maestro = controller_->get_maestro();
		switch((Action)cue[MaestroCueHandler::Byte::ActionByte]) {
			case Action::SetShow:
				maestro->set_show(nullptr, 0);
				break;
			case Action::SetTimer:
				maestro->set_timer(IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Byte::OptionsByte]));
				break;
			case Action::Start:
				maestro->get_timer()->start();
				break;
			case Action::Stop:
				maestro->get_timer()->stop();
				break;
			case Action::Sync:
				maestro->sync(IntByteConvert::byte_to_int(&cue[MaestroCueHandler::Byte::OptionsByte]));
				break;
		}
	}

	MaestroCueHandler::~MaestroCueHandler() { }
}
