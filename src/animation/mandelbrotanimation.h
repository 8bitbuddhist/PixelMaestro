/*
 * Mandelbrot - Draws a Mandlebrot fractal.
 * Core logic provided by Joni Salonen's C fractal library: https://github.com/joni/fractals/
 */

#ifndef MANDELBROTANIMATION_H
#define MANDELBROTANIMATION_H

#include "../core/point.h"
#include "animation.h"

namespace PixelMaestro {
	class MandelbrotAnimation : public Animation {
		public:
			MandelbrotAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~MandelbrotAnimation();
			void set_colors(Colors::RGB *colors, uint8_t num_colors);
			void update();

		private:
			Colors::RGB black_ = {0, 0, 0};

			/// Stores complex real and imaginary numbers for each Pixel.
			double c_real_, c_imaginary_;

			/// Stores the calculated width of the image.
			double image_width_;

			/// Tracks the number of runs through the Mandelbrot function for each Pixel.
			uint8_t iterations_ = 0;

			/// Maximum number of iterations to run. Defaults to num_colors.
			uint8_t max_iterations_ = 10;

			/// Temporary holders for Mandelbrot function.
			double x_, x_2_, y_;
	};
}

#endif // MANDELBROTANIMATION_H
