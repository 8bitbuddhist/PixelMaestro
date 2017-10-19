/*
 * CueInterpreter - Parses Cues and generates a string description of the Cue.
 */

#ifndef CUEINTERPRETER_H
#define CUEINTERPRETER_H

#include <string>
#include "cue/animationcuehandler.h"
#include "cue/canvascuehandler.h"
#include "cue/maestrocuehandler.h"
#include "cue/sectioncuehandler.h"

using namespace PixelMaestro;

class CueInterpreter {
	public:
		CueInterpreter();

		std::string interpret_cue(uint8_t* cue);

	private:
		std::string interpret_animation_cue(uint8_t* cue);
		std::string interpret_canvas_cue(uint8_t* cue);
		std::string interpret_maestro_cue(uint8_t* cue);
		std::string interpret_section_cue(uint8_t* cue);
};

#endif // CUEINTERPRETER_H
