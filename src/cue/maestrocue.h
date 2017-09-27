#ifndef MAESTROCUE_H
#define MAESTROCUE_H

#include "../core/maestro.h"

namespace PixelMaestro {
	class MaestroCue {
		public:
			enum Action {
				SetRefreshInterval
			};

			static void set_refresh_interval(unsigned char* buffer, unsigned short interval);

			static void run(Maestro *maestro, unsigned char *cue);
	};
}

#endif // MAESTROCUE_H
