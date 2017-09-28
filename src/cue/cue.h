#ifndef CUE_H
#define CUE_H

#include "../core/maestro.h"

namespace PixelMaestro {
	class Maestro;
	class Cue {
		public:
			Cue(Maestro* maestro, unsigned char* buffer);
			void initialize_buffer(unsigned char size);
			virtual void run(unsigned char* cue) = 0;

		protected:
			unsigned char* buffer_;
			Maestro* maestro_;
	};
}

#endif // CUE_H
