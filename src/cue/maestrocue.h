#ifndef MAESTROCUE_H
#define MAESTROCUE_H

#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class MaestroCue : public Cue {
		public:
			enum Action {
				SetRefreshInterval
			};

			enum Bit {
				ComponentBit = (int)CueController::Bit::PayloadBit,
				ActionBit,
				OptionsBit
			};

			MaestroCue(Maestro* maestro, unsigned char* buffer) : Cue(maestro, buffer) {}
			void set_refresh_interval(unsigned short interval);
			void run(unsigned char *cue);
	};
}

#endif // MAESTROCUE_H
