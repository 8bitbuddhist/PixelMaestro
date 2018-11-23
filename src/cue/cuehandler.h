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
			explicit CueHandler(CueController* controller) {
				controller_ = controller;
			}
			virtual ~CueHandler() { }
			virtual void run(uint8_t* cue) = 0;

		protected:
			/// The controller managing this Handler.
			CueController* controller_ = nullptr;

			Section* get_section(uint8_t section_id, uint8_t layer_id) const;
			Palette* deserialize_palette(const uint8_t* cue, uint8_t num_colors);
			uint16_t serialize_palette(uint8_t* cue, Palette* palette);
	};
}

#endif // CUEHANDLER_H
