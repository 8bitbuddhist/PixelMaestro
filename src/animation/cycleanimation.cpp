#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Colors::RGB* colors, unsigned short num_colors) : Animation(colors, num_colors) { }

	void CycleAnimation::update(Section* section) {
		section->set_all(&colors_[cycle_index_]);
		update_cycle(0, num_colors_);
	}
}
