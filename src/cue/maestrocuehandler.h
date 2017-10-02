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

			enum Byte {
				HandlerByte = (int)CueController::Byte::PayloadByte,
				ActionByte,
				OptionsByte
			};

			MaestroCueHandler(CueController* controller) : CueHandler(controller) { }
			~MaestroCueHandler();
			void set_refresh_interval(uint16_t interval);
			void run(uint8_t *cue);
	};
}

#endif // MAESTROCUEHANDLER_H
