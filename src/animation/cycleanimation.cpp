#include "cycleanimation.h"

namespace PixelMaestro {
	CycleAnimation::CycleAnimation(Colors::RGB* colors, uint8_t num_colors, uint16_t speed, uint16_t pause) : Animation(colors, num_colors, speed, pause) {
		type_ = Animation::Type::Cycle;
	}

	void CycleAnimation::update(Section* section) {
		section->set_all(&colors_[cycle_index_]);
		update_cycle(0, num_colors_);
	}

	CycleAnimation::~CycleAnimation() {}
}
