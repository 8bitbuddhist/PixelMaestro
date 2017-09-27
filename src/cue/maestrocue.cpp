#include "cue.h"
#include "maestrocue.h"

namespace PixelMaestro {
	void MaestroCue::set_refresh_interval(unsigned char *buffer, unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		unsigned char payload[] = {
			(unsigned char)Cue::Component::Maestro,
			Action::SetRefreshInterval,
			interval_byte.index_0,
			interval_byte.index_1
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void MaestroCue::run(Maestro *maestro, unsigned char *cue) {
		switch((Action)cue[Cue::payload_index_ + 1]) {
			case Action::SetRefreshInterval:
				{
					unsigned int interval = IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 2], cue[Cue::payload_index_ + 3]);
					maestro->set_refresh_interval(interval);
				}
				break;
		}
	}
}
