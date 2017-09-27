#ifndef COMMAND_H
#define COMMAND_H

#include "../core/maestro.h"

namespace PixelMaestro {

	/// Converts an integer value to and from a byte array.
	class IntByteConvert {
		public:
			unsigned char quotient_ = 0;
			unsigned char remainder_ = 0;

			IntByteConvert(unsigned int val) {
				quotient_ = val / 256;
				remainder_ = val % 256;
			}

			static unsigned int byte_to_int(unsigned char quotient, unsigned char remainder) {
				return (quotient * 256) + remainder;
			}
	};

	class Command {
		private:
			static const unsigned char header_len_ = 2;
			static const unsigned char header_[];

		public:
			/// The different components available to run commands against.
			enum class Component {
				Animation,
				Canvas,
				Maestro,
				Section
			};

			static const unsigned char size_index_ = header_len_;
			static const unsigned char checksum_index_ = size_index_ + 1;
			static const unsigned char payload_index_ = checksum_index_ + 1;

			static void build_packet(unsigned char* buffer, unsigned char* data, unsigned char data_size);
			static unsigned char checksum(unsigned char* data, unsigned char data_size);
			static void run(Maestro* maestro, unsigned char* command);
	};
}

#endif // COMMAND_H
