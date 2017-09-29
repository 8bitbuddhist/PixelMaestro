#ifndef CUECONTROLLER_H
#define CUECONTROLLER_H

#include "../core/maestro.h"
#include "cuehandler.h"

namespace PixelMaestro {
	class Maestro;
	class CueHandler;

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

	class CueController {
		public:
			/// Common bit indices for each Cue.
			enum Bit {
				Header1Bit,
				Header2Bit,
				Header3Bit,
				ChecksumBit,
				SizeBit,
				PayloadBit
			};

			/// The different handlers available for running Cues.
			enum Handler {
				AnimationHandler,
				CanvasHandler,
				MaestroHandler,
				SectionHandler
			};

			CueController(Maestro* maestro);
			unsigned char* get_cue();
			CueHandler* get_handler(Handler handler);
			Maestro* get_maestro();
			void set_handlers(Handler* handlers, unsigned char num_handlers);

			void assemble(unsigned char payload_size);
			unsigned char checksum(unsigned char* cue, unsigned char cue_size);
			CueHandler* enable_handler(Handler handler);
			void load(unsigned char* cue);
			void load(unsigned char* cues, unsigned char num_cues);
			void run();

		private:
			/// Header assigned to all outgoing Cues.
			const unsigned char header_[3] = {'P', 'M', 'C'};

			/// Buffer for storing the currently loaded Cue.
			unsigned char cue_[255];

			/// Handlers for incoming Cues.
			CueHandler* handlers_[4];

			/// Maestro that Cues will run on.
			Maestro* maestro_;
	};
}

#endif // CUECONTROLLER_H
