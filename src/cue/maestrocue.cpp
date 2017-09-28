#include "cue.h"
#include "maestrocue.h"

namespace PixelMaestro {
	void MaestroCue::set_refresh_interval(unsigned char *buffer, unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		unsigned char payload[] = {
			(unsigned char)Cue::Component::Maestro,
			Action::SetRefreshInterval,
			interval_byte.converted_0,
			interval_byte.converted_1
		};

		Cue::assemble(buffer, payload, sizeof(payload));
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
