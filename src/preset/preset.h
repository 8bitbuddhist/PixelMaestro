/*
 * Preset.h - Base class for Maestro presets.
 */

#ifndef PRESET_H
#define PRESET_H

#include "../core/maestro.h"

namespace PixelMaestro {
	class Maestro;

	class Preset {
		public:
			virtual ~Preset() {}
			virtual void apply(Maestro* maestro) = 0;
	};
}

#endif // PRESET_H
