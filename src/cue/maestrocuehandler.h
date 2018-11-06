#ifndef MAESTROCUEHANDLER_H
#define MAESTROCUEHANDLER_H

#include "cuecontroller.h"
#include "cuehandler.h"

namespace PixelMaestro {
	class MaestroCueHandler : public CueHandler {
		public:
			enum class Action : uint8_t {
				SetBrightness,
				SetShow,
				SetTimer,
				Start,
				Stop,
				Sync,
				RemoveShow
			};

			enum class Byte : uint8_t {
				HandlerByte = (uint8_t)CueController::Byte::PayloadByte,
				ActionByte,
				OptionsByte
			};

			explicit MaestroCueHandler(CueController* controller) : CueHandler(controller) { }
			~MaestroCueHandler();
			uint8_t* remove_show();
			uint8_t* set_brightness(uint8_t brightness);
			uint8_t* set_show();
			uint8_t* set_timer(uint16_t interval);
			uint8_t* start();
			uint8_t* stop();
			uint8_t* sync(const uint32_t new_time);
			void run(uint8_t *cue);
	};
}

#endif // MAESTROCUEHANDLER_H
