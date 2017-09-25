#ifndef COMMAND_H
#define COMMAND_H

#include "core/maestro.h"

namespace PixelMaestro {

	class IntByteConvert {
		public:
			/// Represents an integer value as two bytes.
			struct IntAsByte {
				unsigned char quotient = 0;
				unsigned char remainder = 0;

				IntAsByte(unsigned int val) {
					quotient = val / 256;
					remainder = val % 256;
				}
			};
			static IntAsByte int_to_byte(unsigned int val) {
				return IntAsByte(val);
			}

			static unsigned int byte_to_int(unsigned char quotient, unsigned char remainder) {
				return (quotient * 256) + remainder;
			}
	};

	class Command {
		public:
			/// The different commands available.
			enum Action : unsigned char {
				/**
				 * Change the Maestro's refresh rate.
				 * args[0] = New refresh rate.
				 */
				MaestroChangeRefreshInterval,

				/**
				 * Adds a Canvas to a Section.
				 * args[0] = Section number.
				 * args[0] = Canvas::CanvasType.
				 */
				SectionAddCanvas
			};

			Command(Action action, unsigned int args[]);
			unsigned char* get_command();
			unsigned short get_length();
			static void run(Maestro* maestro, unsigned char* command);

		private:
			/// Text representation of the command.
			unsigned char* command_;

			/// Number of characters in the command.
			unsigned short length_;

			/// The Maestro that this command will run on.
			Maestro* maestro_ = nullptr;
	};
}

#endif // COMMAND_H
