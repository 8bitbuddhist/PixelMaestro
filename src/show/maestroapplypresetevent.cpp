#include "maestroapplypresetevent.h"

namespace PixelMaestro {
	/**
	 * Applies a Preset to a Maestro.
	 * @param time Time to run the Event.
	 * @param maestro Maestro to apply the Preset to.
	 * @param preset Preset to apply.
	 * @param delete_preset If true, delete the Preset from memory after applying it.
	 */
	MaestroApplyPresetEvent::MaestroApplyPresetEvent(unsigned long time, Maestro *maestro, Preset *preset, bool delete_preset)	: Event(time) {
		this->maestro_ = maestro;
		this->preset_ = preset;
		this->delete_preset_ = delete_preset;
	}

	void MaestroApplyPresetEvent::run() {
		maestro_->apply_preset(preset_, delete_preset_);
	}
}
