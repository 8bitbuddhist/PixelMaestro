#include "../utility.h"
#include "radialanimation.h"

namespace PixelMaestro {
	RadialAnimation::RadialAnimation(Colors::RGB* colors, uint8_t num_colors, uint16_t speed, uint16_t pause) : Animation(colors, num_colors, speed, pause) {
		type_ = AnimationType::Radial;
	}

	void RadialAnimation::update(Section* section) {
		// Check if the size of the grid has changed.
		if (size_ != *section->get_dimensions()) {
			size_ = *section->get_dimensions();
			center_ = {
				(uint16_t)(size_.x / 2),
				(uint16_t)(size_.y / 2)
			};
		}

		if (orientation_ == Orientation::Vertical) {
			// For each Pixel, calculate the slope from the center.
			for (uint16_t y = 0; y < size_.y; y++) {
				for (uint16_t x = 0; x < size_.x; x++) {
					if (x == center_.x || y == center_.y) {
						slope_ = 0;
					}
					else {
						//slope_ = ((center_.y - y) / (float)(center_.x - x)) * 10;
						slope_ = ((y - center_.y) / (float)(x - center_.x)) * 10;
					}

					section->set_one(x, y, get_color_at_index(slope_ + cycle_index_));
				}
			}
		}
		else {	// Horizontal
			// For each Pixel, calculate its distance from the center of the grid, then use the distance to choose the index of the correct color.
			for (uint16_t y = 0; y < size_.y; y++) {
				y_squared_ = Utility::square(y - center_.y);
				for (uint16_t x = 0; x < size_.x; x++) {
					distance_ = Utility::sqrt(Utility::square(x - center_.x) + y_squared_);
					section->set_one(x, y, get_color_at_index(distance_ + cycle_index_));
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	RadialAnimation::~RadialAnimation() {}
}
