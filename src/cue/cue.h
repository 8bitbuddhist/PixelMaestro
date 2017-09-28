#ifndef CUE_H
#define CUE_H

#include "../core/maestro.h"

namespace PixelMaestro {

	/// Converts a float value to and from a byte array.
	class FloatByteConvert {
		public:
			typedef union {
				float val;
				unsigned char byte[4];
			} Converter;

			Converter converted;

			FloatByteConvert(float float_val) {
				converted.val = float_val;
			}

			static float byte_to_float(unsigned char* byte_start) {
				Converter converted_tmp;
				converted_tmp.byte[0] = byte_start[0];
				converted_tmp.byte[1] = byte_start[1];
				converted_tmp.byte[2] = byte_start[2];
				converted_tmp.byte[3] = byte_start[3];

				return converted_tmp.val;
			}
	};

	/// Converts an integer value to and from a byte array.
	class IntByteConvert {
		public:
			unsigned char converted_0 = 0;
			unsigned char converted_1 = 0;

			IntByteConvert(unsigned int val) {
				converted_0 = val / 256;
				converted_1 = val % 256;
			}

			static unsigned int byte_to_int(unsigned char* byte_start) {
				return (byte_start[0] * 256) + byte_start[1];
			}
	};

	class Cue {
		private:
			static const unsigned char header_[];

		public:
			/// Common bit indices in each packet..
			enum Bit {
				Header1Bit,
				Header2Bit,
				Header3Bit,
				ChecksumBit,
				SizeBit,
				PayloadBit
			};

			/// The different components available to run commands against.
			enum class Component {
				Animation,
				Canvas,
				Maestro,
				Section
			};

			static void assemble(unsigned char* buffer, unsigned char payload_size);
			static unsigned char checksum(unsigned char* data, unsigned char data_size);
			static void run(Maestro* maestro, unsigned char* command);
	};
}

#endif // CUE_H
