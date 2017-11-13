#ifndef MAESTROCUEHANDLER_H
#define MAESTROCUEHANDLER_H

#include "cuecontroller.h"
#include "cuehandler.h"

namespace PixelMaestro {
	class MaestroCueHandler : public CueHandler {
		public:
			enum Action : uint8_t {
				SetRefreshInterval
			};

			enum Byte : uint8_t {
				HandlerByte = (uint8_t)CueController::Byte::PayloadByte,
				ActionByte,
				OptionsByte
			};

			MaestroCueHandler(CueController* controller) : CueHandler(controller) { }
			~MaestroCueHandler();
			uint8_t* set_refresh_interval(uint16_t interval);
			void run(uint8_t *cue);
	};
}

#endif // MAESTROCUEHANDLER_H
