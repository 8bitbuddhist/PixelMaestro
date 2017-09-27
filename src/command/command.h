#ifndef COMMAND_H
#define COMMAND_H

#include "../core/maestro.h"

// TODO: Rename to...Cue? Prompt?
namespace PixelMaestro {

	/// Converts an integer value to and from a byte array.
	class IntByteConvert {
		public:
			unsigned char index_0 = 0;
			unsigned char index_1 = 0;

			IntByteConvert(unsigned int val) {
				index_0 = val / 256;
				index_1 = val % 256;
			}

			static unsigned int byte_to_int(unsigned char index0, unsigned char index1) {
				return (index0 * 256) + index1;
			}
	};

	class Command {
		private:
			static const unsigned char header_len_;
			static const unsigned char header_[];

		public:
			/// The different components available to run commands against.
			enum class Component {
				Animation,
				Canvas,
				Maestro,
				Section
			};

			static unsigned char size_index_;
			static unsigned char checksum_index_;
			static unsigned char payload_index_;

			static void assemble(unsigned char* buffer, unsigned char* data, unsigned char data_size);
			static unsigned char checksum(unsigned char* data, unsigned char data_size);
			static void run(Maestro* maestro, unsigned char* command);
	};
}

#endif // COMMAND_H
