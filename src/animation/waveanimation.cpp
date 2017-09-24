#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Colors::RGB* colors, unsigned char num_colors, unsigned short speed, unsigned short pause) : Animation(colors, num_colors, speed, pause) { }

	void WaveAnimation::update(Section* section) {
		for (unsigned short y = 0; y < section->get_dimensions()->y; y++) {
			for (unsigned short x = 0; x < section->get_dimensions()->x; x++) {
				if (orientation_ == VERTICAL) {
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
