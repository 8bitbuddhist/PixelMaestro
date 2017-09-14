#include "../utility.h"
#include "mandelbrotanimation.h"

namespace PixelMaestro {
	MandelbrotAnimation::MandelbrotAnimation(Colors::RGB* colors, unsigned char num_colors) : Animation(colors, num_colors) { }

	void MandelbrotAnimation::update(Section* section) {
		if (size_ != *section->get_dimensions()) {
			size_ = *section->get_dimensions();

			// Recalculate center and width in case the Section size has changed.
			center_ = {
				(unsigned short)(section->get_dimensions()->x / 2),
				(unsigned short)(section->get_dimensions()->y / 2)
			};

			// Calculate the scale of the pattern
			image_width_ = 4.0 / size_.x;
		}

		// FIXME: Fix image generation. Results are not quite what you'd expect from a Mandelbrot
		for (unsigned short y = 0; y < size_.y; y++) {
			c_imaginary_ = (y - center_.y) * image_width_;
			for (unsigned short x = 0; x < size_.x; x++) {
				c_real_ = (x - center_.x) * image_width_;

				x_ = 0;
				y_ = 0;
				iterations_ = 0;

				while ((x_ * x_) + (y_ * y_) < 4 && iterations_ < max_iterations_) {
					// Default threshold is 2 * x_ * y_
					y_ = (2.75 * x_ * y_) + c_imaginary_;
					x_ = (x_ * x_) - (y_ * y_) + c_real_;
					iterations_++;
				}

				// TODO: Support vertical orientation
				if (iterations_ < max_iterations_) {
					section->set_one(x, y, get_color_at_index(iterations_ + cycle_index_));
				}
				else {
					section->set_one(x, y, &Colors::BLACK);
				}
			}
		}

		update_cycle(0, num_colors_);
	}
}
