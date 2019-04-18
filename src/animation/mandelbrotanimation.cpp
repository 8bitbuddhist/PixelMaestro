#include "../utility.h"
#include "mandelbrotanimation.h"

namespace PixelMaestro {
	MandelbrotAnimation::MandelbrotAnimation(Section& section) : MappedAnimation(section) {
		type_ = AnimationType::Mandelbrot;
		map();
	}

	void MandelbrotAnimation::map() {
		// Initialize Mandelbrot calculation variables
		Point center = get_center();	// Used to center the Mandelbrot on the grid.

		// Calculate the size/scale of the pattern
		double image_width_ = 4.0 / dimensions_.x;

		for (uint16_t y = 0; y < dimensions_.y; y++) {
			double c_imaginary = (y - center.y) * image_width_;
			for (uint16_t x = 0; x < dimensions_.x; x++) {
				double c_real = (x - center.x) * image_width_;

				double temp_x = 0;
				double temp_y = 0;
				iterations_ = 0;

				while ((temp_x * temp_x) + (temp_y * temp_y) < 4 && iterations_ < max_iterations_) {
					double temp_x_2 = (temp_x * temp_x) - (temp_y * temp_y) + c_real;
					temp_y = (2.0 * temp_x * temp_y) + c_imaginary;
					temp_x = temp_x_2;
					iterations_++;
				}

				if (iterations_ < max_iterations_) {
					map_[y][x] = iterations_;
				}
				else {
					map_[y][x] = 255;
				}
			}
		}
	}

	/**
	 * Overrides Animation::SetColors.
	 * Sets the number of iterations equal to the number of colors
	 * @param colors
	 * @param num_colors
	 */
	void MandelbrotAnimation::set_palette(const Colors::RGB colors[], uint8_t num_colors) {
		palette_->set_colors(colors, num_colors);
		max_iterations_ = num_colors;
	}

	void MandelbrotAnimation::update() {
		MappedAnimation::update();

		update_cycle(0, palette_->get_num_colors());
	}
}
