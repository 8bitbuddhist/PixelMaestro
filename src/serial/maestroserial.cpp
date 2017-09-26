#include "serial.h"
#include "maestroserial.h"

namespace PixelMaestro {
	void MaestroSerial::set_refresh_interval(unsigned char *buffer, unsigned short interval) {
		IntByteConvert interval_byte = IntByteConvert(interval);

		unsigned char payload[] = {
			(unsigned char)Serial::Component::Maestro,
			Action::SetRefreshInterval,
			interval_byte.quotient_,
			interval_byte.remainder_
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void MaestroSerial::run(Maestro *maestro, unsigned char *buffer) {
		switch((Action)buffer[Serial::payload_index_ + 1]) {
			case Action::SetRefreshInterval:
				{
					unsigned int interval = IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 2], buffer[Serial::payload_index_ + 3]);
					maestro->set_refresh_interval(interval);
				}
				break;
		}
	}
}
