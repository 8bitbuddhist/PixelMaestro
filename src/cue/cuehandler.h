#ifndef CUEHANDLER_H
#define CUEHANDLER_H

#include <stdint.h>
#include "cuecontroller.h"

namespace PixelMaestro {
	class CueController;
	class CueHandler {
		public:
			CueHandler(CueController* controller) {
				controller_ = controller;
			}
			virtual ~CueHandler() { }
			virtual void run(uint8_t* cue) = 0;

		protected:
			/// The controller managing this Handler.
			CueController* controller_ = nullptr;
	};
}

#endif // CUEHANDLER_H
