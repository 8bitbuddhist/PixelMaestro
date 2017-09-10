#include "../utility.h"
#include "mandelbrotanimation.h"

namespace PixelMaestro {
	MandelbrotAnimation::MandelbrotAnimation(Section *section, Colors::RGB* colors, unsigned short num_colors) : Animation(section, colors, num_colors) { }

	void MandelbrotAnimation::update() {
		// Recalculate center and width in case the Section size has changed.
		center_ = {
			(short)(section_->get_dimensions()->x / 2),
			(short)(section_->get_dimensions()->y / 2)
		};
		image_width_ = 4.0 / section_->get_dimensions()->x;

		// TODO: Fix image generation. Results are not quite what you'd expect from a Mandelbrot
		for (unsigned short row = 0; row < section_->get_dimensions()->y; row++) {
			for (unsigned short column = 0; column < section_->get_dimensions()->x; column++) {
				c_real_ = (column - center_.x) * image_width_;
				c_imaginary_ = (row - center_.y) * image_width_;

				x_ = 0;
				y_ = 0;
				iterations_ = 0;

				while (x_ * x_ + y_ * y_ < 4 && iterations_ < max_) {
					y_ = 2 * x_ * y_ + c_imaginary_;
					x_ = x_ * x_ + y_ * y_ + c_real_;
					iterations_++;
				}

				if (orientation_ == Orientations::VERTICAL) {
					if (iterations_ < max_) {
						section_->set_one(column, row, get_color_at_index(iterations_ + cycle_index_));
					}
					else {
						section_->set_one(column, row, &Colors::BLACK);
					}
				}
				else {	// Horizontal
					if (iterations_ < max_) {
						section_->set_one(row, column, get_color_at_index(iterations_ + cycle_index_));
					}
					else {
						section_->set_one(row, column, &Colors::BLACK);
					}
				}

			}
		}

		update_cycle(0, num_colors_);
	}
}
