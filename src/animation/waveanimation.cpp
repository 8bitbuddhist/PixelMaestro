#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Colors::RGB* colors, uint8_t num_colors) : Animation(colors, num_colors) {
		type_ = AnimationType::Wave;
	}

	void WaveAnimation::update(Section* section) {
		for (uint16_t y = 0; y < section->get_dimensions()->y; y++) {
			for (uint16_t x = 0; x < section->get_dimensions()->x; x++) {
				if (orientation_ == Vertical) {
					section->set_one(x, y, get_color_at_index(y + cycle_index_));
				}
				else {	// Horizontal
					section->set_one(x, y, get_color_at_index(x + cycle_index_));
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	WaveAnimation::~WaveAnimation() {}
}
