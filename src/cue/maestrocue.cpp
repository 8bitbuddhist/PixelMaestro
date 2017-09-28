#include "cuecontroller.h"
#include "maestrocue.h"

namespace PixelMaestro {
	void MaestroCue::set_refresh_interval(unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::MaestroComponent;
		buffer_[Bit::ActionBit] = Action::SetRefreshInterval;
		buffer_[Bit::OptionsBit] = interval_byte.converted_0;
		buffer_[Bit::OptionsBit + 1] = interval_byte.converted_1;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 2));
	}

	void MaestroCue::run(unsigned char *cue) {
		switch((Action)cue[MaestroCue::Bit::ActionBit]) {
			case Action::SetRefreshInterval:
				{
					unsigned int interval = IntByteConvert::byte_to_int(&cue[MaestroCue::Bit::OptionsBit]);
					maestro_->set_refresh_interval(interval);
				}
				break;
		}
	}
}
