#ifndef SHOWCUEHANDLER_H
#define SHOWCUEHANDLER_H

#include "cuehandler.h"
#include "cuecontroller.h"
#include "show.h"

namespace PixelMaestro {
	class ShowCueHandler : public CueHandler {
		public:
			enum class Action : uint8_t {
				SetEvents,
				SetLooping,
				SetTimingMode
			};

			enum class Byte : uint8_t {
				HandlerByte = (uint8_t)CueController::Byte::PayloadByte,
				ActionByte,
				OptionsByte
			};

			explicit ShowCueHandler(CueController& controller) : CueHandler(controller) { }
			~ShowCueHandler() = default;

			uint8_t* set_events(Event* events, uint16_t num_events, bool preserve_current_index = true);
			uint8_t* set_looping(bool loop);
			uint8_t* set_timing_mode(Show::TimingMode timing);
			void run(uint8_t *cue);
	};
}

#endif // SHOWCUEHANDLER_H
