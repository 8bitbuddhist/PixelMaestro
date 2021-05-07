#include "../utility.h"
#include "mandelbrotanimation.h"

namespace PixelMaestro {
	MandelbrotAnimation::MandelbrotAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Mandelbrot;
		map();
	}

	// FIXME: Fix Animations on Arduinos, likely caused by rounding errors.
	void MandelbrotAnimation::map() {
		if (orientation_ == Orientation::Horizontal || orientation_ == Orientation::HorizontalFlipped) {
			// Calculate the size/scale of the pattern
			float image_width = 4.0F / static_cast<float>(dimensions_.x);

			for (uint16_t y = 0; y < dimensions_.y; y++) {
				float c_imaginary = (y - center_.y) * image_width;
				for (uint16_t x = 0; x < dimensions_.x; x++) {
					float c_real = (x - center_.x) * image_width;

					float temp_x = 0;
					float temp_y = 0;
					iterations_ = 0;

					while (iterations_ < max_iterations_ && ((temp_x * temp_x) + (temp_y * temp_y)) < 4.0F) {
						float temp_x_2 = ((temp_x * temp_x) - (temp_y * temp_y)) + c_real;
						temp_y = (2.0F * temp_x * temp_y) + c_imaginary;
						temp_x = temp_x_2;
						++iterations_;
					}

					if (iterations_ < max_iterations_) {
						set_map_color_index(x, y, iterations_);
					}
					else {
						set_map_color_index(x, y, 255);
					}
				}
			}
		}
		else { // Vertical orientation
			float image_width = 4.0F / static_cast<float>(dimensions_.y);

			for (uint16_t x = 0; x < dimensions_.x; x++) {
				float c_imaginary = (x - center_.x) * image_width;
				for (uint16_t y = 0; y < dimensions_.y; y++) {
					float c_real = (y - center_.y) * image_width;

					float temp_x = 0;
					float temp_y = 0;
					iterations_ = 0;

					while (iterations_ < max_iterations_ && ((temp_y * temp_y) + (temp_x * temp_x)) < 4.0F) {
						float temp_y_2	= ((temp_y * temp_y) - (temp_x * temp_x)) + c_real;
						temp_x = (2.0F * temp_x * temp_y) + c_imaginary;
						temp_y = temp_y_2;
						++iterations_;
					}

					if (iterations_ < max_iterations_) {
						set_map_color_index(x, y, iterations_);
					}
					else {
						set_map_color_index(x, y, 255);
					}
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
		update_frame(0, palette_->get_num_colors());
	}
}
