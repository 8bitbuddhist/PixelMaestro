/*
 * CueController - Class for converting PixelMaestro commands to and from serialized strings.
 */

#ifndef CUECONTROLLER_H
#define CUECONTROLLER_H

#include <stdint.h>
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
				uint8_t byte[4];
			} Converter;

			Converter converted;

			explicit FloatByteConvert(float float_val) {
				converted.val = float_val;
			}

			static float byte_to_float(uint8_t* byte_start) {
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
			uint8_t converted_0 = 0, converted_1 = 0, converted_2 = 0, converted_3 = 0;

			explicit IntByteConvert(uint32_t val) {
				converted_0 = val;
				converted_1 = val >> 8;
				converted_2 = val >> 16;
				converted_3 = val >> 24;
			}

			static uint16_t byte_to_uint16(uint8_t* byte_start) {
				return byte_start[0] | (byte_start[1] << 8);
			}

			static uint32_t byte_to_uint32(uint8_t* byte_start) {
				return byte_start[0] | (byte_start[1] << 8) | (byte_start[2] << 16) | (byte_start[3] << 24);
			}
	};

	class CueController {
		public:
			/// Common bit indices for each Cue.
			enum class Byte : uint8_t {
				IDByte1,
				IDByte2,
				IDByte3,
				ChecksumByte,
				SizeByte1,
				SizeByte2,
				SizeByte3,
				SizeByte4,
				PayloadByte
			};

			/// The different handlers available for running Cues.
			enum class Handler : uint8_t {
				AnimationCueHandler,
				CanvasCueHandler,
				MaestroCueHandler,
				SectionCueHandler,
				ShowCueHandler
			};

			CueController(Maestro& maestro, uint32_t buffer_size = UINT8_MAX);
			~CueController();
			uint8_t* assemble(uint32_t payload_size);
			uint8_t checksum(const uint8_t* cue, uint32_t cue_size);
			CueHandler& enable_animation_cue_handler();
			CueHandler& enable_canvas_cue_handler();
			CueHandler& enable_maestro_cue_handler();
			CueHandler& enable_section_cue_handler();
			CueHandler& enable_show_cue_handler();
			uint8_t* get_buffer() const;
			uint32_t get_buffer_size() const;
			uint32_t get_cue_size() const;
			uint32_t get_cue_size(uint8_t* cue) const;
			CueHandler* get_handler(Handler handler) const;
			Maestro& get_maestro() const;
			bool read(uint8_t byte);
			void run();
			void run(uint8_t* cue);
			bool validate_header(uint8_t* cue);

		private:
			/// Size of the buffer for caching Cues.
			uint32_t buffer_size_;

			/// Buffer for storing the currently loaded Cue.
			uint8_t* buffer_ = nullptr;

			/// Handlers for incoming Cues.
			CueHandler* handlers_[5] {nullptr};

			/// Unique ID marking the start of a Cue.
			const uint8_t id_[3] = {'P', 'M', 'C'};

			/// Maestro that Cues will run on.
			Maestro& maestro_;

			/// Index for tracking buffer reads while loading a Cue by byte.
			uint32_t read_index_ = 0;
	};
}

#endif // CUECONTROLLER_H
