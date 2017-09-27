#ifndef MAESTROCOMMAND_H
#define MAESTROCOMMAND_H

#include "../core/maestro.h"

namespace PixelMaestro {
	class MaestroCommand {
		public:
			enum Action {
				SetRefreshInterval
			};

			static void set_refresh_interval(unsigned char* buffer, unsigned short interval);

			static void run(Maestro *maestro, unsigned char *buffer);
	};
}

#endif // MAESTROCOMMAND_H
