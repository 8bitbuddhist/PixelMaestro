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

			double image_width_;

			int iterations_;

			const int max_ = 10;

			double x_, y_;
	};
}

#endif // MANDELBROTANIMATION_H
