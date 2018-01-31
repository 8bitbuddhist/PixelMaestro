#include "../utility.h"
#include "mandelbrotanimation.h"

namespace PixelMaestro {
	MandelbrotAnimation::MandelbrotAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors) : Animation(section, colors, num_colors) {
		type_ = AnimationType::Mandelbrot;
	}

	/**
	 * Overrides Animation::SetColors.
	 * Sets the number of iterations equal to the number of colors
	 * @param colors
	 * @param num_colors
	 */
	void MandelbrotAnimation::set_colors(Colors::RGB *colors, uint8_t num_colors) {
		colors_ = colors;
		num_colors_ = num_colors;
		max_iterations_ = num_colors;
	}

	void MandelbrotAnimation::update() {
		Point center = get_center();
		// Calculate the scale of the pattern
		image_width_ = 4.0 / section_->get_dimensions()->x;

		for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
			c_imaginary_ = (y - center.y) * image_width_;
			for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
				c_real_ = (x - center.x) * image_width_;

				x_ = 0;
				y_ = 0;
				iterations_ = 0;

				while ((x_ * x_) + (y_ * y_) < 4 && iterations_ < max_iterations_) {
					x_2_ = (x_ * x_) - (y_ * y_) + c_real_;
					y_ = (2.0 * x_ * y_) + c_imaginary_;
					x_ = x_2_;
					iterations_++;
				}

				if (orientation_ == Orientation::Vertical) {
					if (iterations_ < max_iterations_) {
						section_->set_one(y, x, get_color_at_index(iterations_ + cycle_index_));
					}
					else {
						section_->set_one(y, x, &black_);
					}
				}
				else {
					if (iterations_ < max_iterations_) {
						section_->set_one(x, y, get_color_at_index(iterations_ + cycle_index_));
					}
					else {
						section_->set_one(x, y, &black_);
					}
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	MandelbrotAnimation::~MandelbrotAnimation() {}
}
