#ifndef MAESTROCUE_H
#define MAESTROCUE_H

#include "../core/maestro.h"
#include "cue.h"

namespace PixelMaestro {
	class MaestroCue {
		public:
			enum Action {
				SetRefreshInterval
			};

			enum Bit {
				ComponentBit = (int)Cue::Bit::PayloadBit,
				ActionBit,
				OptionsBit
			};

			static void set_refresh_interval(unsigned char* buffer, unsigned short interval);

			static void run(Maestro *maestro, unsigned char *cue);
	};
}

#endif // MAESTROCUE_H
