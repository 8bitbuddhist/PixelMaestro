#ifndef CUEHANDLER_H
#define CUEHANDLER_H

#include "cuecontroller.h"

namespace PixelMaestro {
	class CueController;
	class CueHandler {
		public:
			CueHandler(CueController* controller);
			virtual void run(unsigned char* cue) = 0;

		protected:
			/// The controller managing this Handler.
			CueController* controller_;
	};
}

#endif // CUEHANDLER_H
