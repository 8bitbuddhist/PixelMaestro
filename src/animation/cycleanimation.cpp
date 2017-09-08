#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void CycleAnimation::update() {
		section_->set_all(&colors_[cycle_index_]);
		update_cycle(0, num_colors_);
	}
}
