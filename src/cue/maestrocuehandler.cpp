#include "cuecontroller.h"
#include "maestrocuehandler.h"
#include "showcuehandler.h"

namespace PixelMaestro {

	uint8_t* MaestroCueHandler::remove_show() {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::MaestroCueHandler,
			(uint8_t)Action::RemoveShow
		);

		return controller_.assemble(++index);
	}

	uint8_t* MaestroCueHandler::set_brightness(uint8_t brightness) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::MaestroCueHandler,
			(uint8_t)Action::SetBrightness
		);
		controller_.get_buffer()[++index] = brightness;

		return controller_.assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* MaestroCueHandler::set_show() {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::MaestroCueHandler,
			(uint8_t)Action::SetShow
		);

		return controller_.assemble(++index);
	}

	uint8_t* MaestroCueHandler::set_timer(uint16_t interval) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::MaestroCueHandler,
			(uint8_t)Action::SetTimer
		);
		add_uint16_to_cue(index, interval);

		return controller_.assemble(++index);
	}

	uint8_t* MaestroCueHandler::start() {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::MaestroCueHandler,
			(uint8_t)Action::Start
		);

		return controller_.assemble(++index);
	}

	uint8_t* MaestroCueHandler::stop() {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::MaestroCueHandler,
			(uint8_t)Action::Stop
		);

		return controller_.assemble(++index);
	}

	uint8_t* MaestroCueHandler::sync(const uint32_t new_time) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::MaestroCueHandler,
			(uint8_t)Action::Sync
		);

		add_uint32_to_cue(index, new_time);

		return controller_.assemble(++index);
	}

	void MaestroCueHandler::run(uint8_t *cue) {
		Maestro& maestro = controller_.get_maestro();
		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::RemoveShow:
				maestro.remove_show();
				break;
			case Action::SetBrightness:
				maestro.set_brightness(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetShow:
				maestro.set_show(nullptr, 0);
				break;
			case Action::SetTimer:
				maestro.set_timer(IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]));
				break;
			case Action::Start:
				maestro.get_timer().start();
				break;
			case Action::Stop:
				maestro.get_timer().stop();
				break;
			case Action::Sync:
				maestro.sync(IntByteConvert::byte_to_uint32(&cue[(uint8_t)Byte::OptionsByte]));
				break;
		}
	}
}
