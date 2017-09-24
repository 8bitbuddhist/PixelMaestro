#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Colors::RGB* colors, unsigned char num_colors, unsigned short speed, unsigned short pause) : Animation(colors, num_colors, speed, pause) { }

	void CycleAnimation::update(Section* section) {
		section->set_all(&colors_[cycle_index_]);
		update_cycle(0, num_colors_);
	}

	CycleAnimation::~CycleAnimation() {}
}
