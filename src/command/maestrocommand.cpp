#include "command.h"
#include "maestrocommand.h"

namespace PixelMaestro {
	void MaestroCommand::set_refresh_interval(unsigned char *buffer, unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		unsigned char payload[] = {
			(unsigned char)Command::Component::Maestro,
			Action::SetRefreshInterval,
			interval_byte.quotient_,
			interval_byte.remainder_
		};

		Command::build_packet(buffer, payload, sizeof(payload));
	}

	void MaestroCommand::run(Maestro *maestro, unsigned char *buffer) {
		switch((Action)buffer[Command::payload_index_ + 1]) {
			case Action::SetRefreshInterval:
				{
					unsigned int interval = IntByteConvert::byte_to_int(buffer[Command::payload_index_ + 2], buffer[Command::payload_index_ + 3]);
					maestro->set_refresh_interval(interval);
				}
				break;
		}
	}
}
