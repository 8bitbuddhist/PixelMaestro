/*
 * CueHandler - Base class for mapping Cues to PixelMaestro actions.
 */

#ifndef CUEHANDLER_H
#define CUEHANDLER_H

#include <stdint.h>
#include "../core/palette.h"
#include "../core/section.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class CueController;
	class CueHandler {
		public:
			explicit CueHandler(CueController& controller);
			virtual ~CueHandler() { }
			virtual void run(uint8_t* cue) = 0;

		protected:
			/// The controller managing this Handler.
			CueController& controller_;

			void add_float_to_cue(uint32_t& index, float value);
			void add_uint16_to_cue(uint32_t& index, uint16_t value);
			void add_uint32_to_cue(uint32_t& index, uint32_t value);
			Section* get_section(uint8_t section_id, uint8_t layer_id) const;
			Palette* deserialize_palette(const uint8_t* cue, uint8_t num_colors);
			uint16_t serialize_palette(uint8_t cue[], const Palette& palette);
			uint32_t start_cue(uint8_t handler_byte, uint8_t action_byte);
			uint32_t start_cue(uint8_t handler_byte, uint8_t action_byte, uint8_t section_num, uint8_t layer_num);
	};
}

#endif // CUEHANDLER_H
