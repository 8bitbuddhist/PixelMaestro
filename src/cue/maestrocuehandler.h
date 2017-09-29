#ifndef MAESTROCUEHANDLER_H
#define MAESTROCUEHANDLER_H

#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class MaestroCueHandler : public CueHandler {
		public:
			enum Action {
				SetRefreshInterval
			};

			enum Bit {
				HandlerBit = (int)CueController::Bit::PayloadBit,
				ActionBit,
				OptionsBit
			};

			MaestroCueHandler(CueController* controller) : CueHandler(controller) { }
			void set_refresh_interval(unsigned short interval);
			void run(unsigned char *cue);
	};
}

#endif // MAESTROCUEHANDLER_H
