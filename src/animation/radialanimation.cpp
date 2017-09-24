#include "../utility.h"
#include "radialanimation.h"

namespace PixelMaestro {
	RadialAnimation::RadialAnimation(Colors::RGB* colors, unsigned char num_colors, unsigned short speed, unsigned short pause) : Animation(colors, num_colors, speed, pause) { }

	void RadialAnimation::update(Section* section) {
		// Check if the size of the grid has changed.
		if (size_ != *section->get_dimensions()) {
			size_ = *section->get_dimensions();
			center_ = {
				(unsigned short)(size_.x / 2),
				(unsigned short)(size_.y / 2)
			};
		}

		if (orientation_ == Orientations::VERTICAL) {
			// For each Pixel, calculate the slope from the center.
			for (unsigned short y = 0; y < size_.y; y++) {
				for (unsigned short x = 0; x < size_.x; x++) {
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
			for (unsigned short y = 0; y < size_.y; y++) {
				y_squared_ = Utility::square(y - center_.y);
				for (unsigned short x = 0; x < size_.x; x++) {
					distance_ = Utility::sqrt(Utility::square(x - center_.x) + y_squared_);
					section->set_one(x, y, get_color_at_index(distance_ + cycle_index_));
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	RadialAnimation::~RadialAnimation() {}
}
