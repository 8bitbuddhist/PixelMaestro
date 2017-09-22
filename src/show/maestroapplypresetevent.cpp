#include "maestroapplypresetevent.h"

namespace PixelMaestro {
	MaestroApplyPresetEvent::MaestroApplyPresetEvent(unsigned long time, Maestro *maestro, Preset *preset)	: Event(time) {
		this->maestro_ = maestro;
		this->preset_ = preset;
	}

	void MaestroApplyPresetEvent::run() {
		maestro_->apply_preset(preset_);
	}
}
