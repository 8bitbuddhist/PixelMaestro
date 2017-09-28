#include "cue.h"
#include "maestrocue.h"

namespace PixelMaestro {
	void MaestroCue::set_refresh_interval(unsigned char *buffer, unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		buffer[Bit::ComponentBit] = (unsigned char)Cue::Component::Maestro;
		buffer[Bit::ActionBit] = Action::SetRefreshInterval;
		buffer[Bit::OptionsBit] = interval_byte.converted_0;
		buffer[Bit::OptionsBit + 1] = interval_byte.converted_1;

		Cue::assemble(buffer, (unsigned char)(Bit::OptionsBit + 2));
	}

	void MaestroCue::run(Maestro *maestro, unsigned char *cue) {
		switch((Action)cue[MaestroCue::Bit::ActionBit]) {
			case Action::SetRefreshInterval:
				{
					unsigned int interval = IntByteConvert::byte_to_int(&cue[MaestroCue::Bit::OptionsBit]);
					maestro->set_refresh_interval(interval);
				}
				break;
		}
	}
}
