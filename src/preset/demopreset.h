#ifndef DEMOPRESET_H
#define DEMOPRESET_H

#include "../core/maestro.h"
#include "preset.h"

namespace PixelMaestro {
	class DemoPreset : public Preset {
		public:
			~DemoPreset();
			void apply(Maestro *maestro);
	};
}

#endif // DEMOPRESET_H
