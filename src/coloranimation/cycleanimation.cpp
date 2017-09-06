#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Section* section, bool reverse, Orientations orientation) : ColorAnimation(section, reverse, orientation) { }

	void CycleAnimation::update() {
		section_->set_all(&colors_[cycle_index_]);
		update_cycle(0, num_colors_);
	}
}
