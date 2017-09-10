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
			MandelbrotAnimation(Section* section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();

		private:

			/// Stores complex real and imaginary numbers for each Pixel.
			double c_real_, c_imaginary_;

			/// The center of the image.
			Point center_ = {0, 0};

			/// Stores the calculated width of the image.
			double image_width_;

			/// Tracks the number of runs through the Mandelbrot function for each Pixel.
			int iterations_ = 0;

			/// Maximum number of iterations to run.
			const int max_iterations_ = 10;

			/// Stores grid size for comparison.
			Point size_ = {0, 0};

			/// Temporary holders for Mandelbrot function.
			double x_, y_;
	};
}

#endif // MANDELBROTANIMATION_H
