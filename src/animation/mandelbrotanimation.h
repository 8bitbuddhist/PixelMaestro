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
			MandelbrotAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned short speed = 100, unsigned short pause = 0);
			void set_colors(Colors::RGB *colors, unsigned char num_colors);
			void update(Section* section);

		private:

			/// Stores complex real and imaginary numbers for each Pixel.
			double c_real_, c_imaginary_;

			/// The center of the image.
			Point center_ = {0, 0};

			/// Stores the calculated width of the image.
			double image_width_;

			/// Tracks the number of runs through the Mandelbrot function for each Pixel.
			unsigned char iterations_ = 0;

			/// Maximum number of iterations to run. Defaults to num_colors.
			unsigned char max_iterations_ = 10;

			/// Stores grid size for comparison.
			Point size_ = {0, 0};

			/// Temporary holders for Mandelbrot function.
			double x_, x_2_, y_;
	};
}

#endif // MANDELBROTANIMATION_H
