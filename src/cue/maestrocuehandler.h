#ifndef MAESTROCUEHANDLER_H
#define MAESTROCUEHANDLER_H

#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class MaestroCueHandler : public CueHandler {
		public:
			enum Action : uint8_t {
				SetRefreshInterval
			};

			enum Byte : uint8_t {
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
