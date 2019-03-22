#include "solidanimation.h"

namespace PixelMaestro {
	SolidAnimation::SolidAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Solid;
	}

	void SolidAnimation::update() {
		if (orientation_ == Orientation::Vertical) {
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					section_->set_one(x, y, palette_->get_color_at_index(y), timer_->get_step_count());
				}
			}
		}
		else {	// Horizontal
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					section_->set_one(x, y, palette_->get_color_at_index(x), timer_->get_step_count());
				}
			}
		}
	}
}
