#include "../utility.h"
#include "mandelbrotanimation.h"

namespace PixelMaestro {
	MandelbrotAnimation::MandelbrotAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void MandelbrotAnimation::update() {
		if (size_ != *section_->get_dimensions()) {
			size_ = *section_->get_dimensions();

			// Recalculate center and width in case the Section size has changed.
			center_ = {
				(short)(section_->get_dimensions()->x * 0.8),
				(short)(section_->get_dimensions()->y / 2)
			};
			image_width_ = 4.0 / size_.x;
		}

		// TODO: Fix image generation. Results are not quite what you'd expect from a Mandelbrot
		for (unsigned short y = 0; y < size_.y; y++) {
			for (unsigned short x = 0; x < size_.x; x++) {
				c_real_ = (x - center_.x) * image_width_;
				c_imaginary_ = (y - center_.y) * image_width_;

				x_ = 0;
				y_ = 0;
				iterations_ = 0;

				while (x_ * x_ + y_ * y_ < 4 && iterations_ < max_iterations_) {
					y_ = 2 * x_ * y_ + c_imaginary_;
					x_ = x_ * x_ + y_ * y_ + c_real_;
					iterations_++;
				}

				// TODO: Support vertical orientation
				if (iterations_ < max_iterations_) {
					section_->set_one(x, y, get_color_at_index(iterations_ + cycle_index_));
				}
				else {
					section_->set_one(x, y, &Colors::BLACK);
				}
			}
		}

		update_cycle(0, num_colors_);
	}
}
