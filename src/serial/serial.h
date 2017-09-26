#ifndef SERIAL_H
#define SERIAL_H

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

	/**
	 * Converts an unsigned long to and from a byte array.
	 * See http://rclermont.blogspot.com/2010/02/convert-long-into-byte-array-in-cc.html
	 */
	class LongByteConvert {
		public:
			unsigned char index_0_ = 0;
			unsigned char index_1_ = 0;
			unsigned char index_2_ = 0;
			unsigned char index_3_ = 0;

			LongByteConvert(unsigned long val) {
				index_0_ = (int)((val >> 24) & 0xFF);
				index_1_ = (int)((val >> 16) & 0xFF);
				index_2_ = (int)((val >> 8) & 0xFF);
				index_3_ = (int)(val & 0xFF);
			}

			static unsigned long byte_to_long(unsigned char index_0, unsigned char index_1, unsigned char index_2, unsigned char index_3) {
				return ((index_0 << 24) +
						(index_1 << 16) +
						(index_2 << 8) +
						index_3);
			}
	};

	class Serial {
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

			/// The different commands available.
			enum Action : unsigned char {

				/**
				 * Clears a Canvas.
				 * args[0] = Section that the Canvas belongs to.
				 */
				CanvasClear,

				/**
				 * Draws a circle onto a Canvas.
				 * args[0] = Section that the Canvas belongs to.
				 * args[1] = Type of Canvas.
				 * args[2] = Origin x coordinate.
				 * args[3] = Origin y coordinate.
				 * args[4] = Radius.
				 * args[5] = If true, fill the circle.
				 * args[6] = If a ColorCanvas, the r value of the color to use.
				 * args[7] = If a ColorCanvas, the g value of the color to use.
				 * args[8] = If a ColorCanvas, the b value of the color to use.
				 */
				CanvasDrawCircle,

				CanvasDrawLine,

				CanvasDrawPoint,

				CanvasDrawRect,

				CanvasDrawText,

				CanvasDrawTriangle,

				MaestroApplyPreset,

				MaestroSetRunning,

				/**
				 * Changes the Maestro's refresh rate.
				 * args[0] = New refresh rate.
				 */
				MaestroChangeRefreshInterval
			};

			Serial(Action action, unsigned int args[]);

			static bool run_checksum;
			static const unsigned char size_index_ = header_len_;
			static const unsigned char checksum_index_ = size_index_ + 1;
			static const unsigned char payload_index_ = checksum_index_ + 1;

			static void build_packet(unsigned char* buffer, unsigned char* data, unsigned char data_size);
			static unsigned char checksum(unsigned char* data, unsigned char data_size);
			static void run(Maestro* maestro, unsigned char* command);
	};
}

#endif // SERIAL_H
