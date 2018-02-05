#ifndef MAESTROCUEHANDLER_H
#define MAESTROCUEHANDLER_H

#include "cuecontroller.h"
#include "cuehandler.h"

namespace PixelMaestro {
	class MaestroCueHandler : public CueHandler {
		public:
			enum Action : uint8_t {
				SetShow,
				SetTiming,
				Start,
				Stop,
				Sync
			};

			enum Byte : uint8_t {
				HandlerByte = (uint8_t)CueController::Byte::PayloadByte,
				ActionByte,
				OptionsByte
			};

			MaestroCueHandler(CueController* controller) : CueHandler(controller) { }
			~MaestroCueHandler();
			uint8_t* set_show(Event* events = nullptr, uint16_t num_events = 0, bool preserve_event_index = true);
			uint8_t* set_timing(uint16_t interval);
			uint8_t* start();
			uint8_t* stop();
			uint8_t* sync(const uint32_t new_time);
			void run(uint8_t *cue);
	};
}

#endif // MAESTROCUEHANDLER_H
