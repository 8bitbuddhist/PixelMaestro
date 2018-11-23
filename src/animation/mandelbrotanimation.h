/*
 * Mandelbrot - Draws a Mandlebrot fractal.
 * Core logic provided by Joni Salonen's C fractal library: https://github.com/joni/fractals/
 */

#ifndef MANDELBROTANIMATION_H
#define MANDELBROTANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class MandelbrotAnimation : public MappedAnimation {
		public:
			explicit MandelbrotAnimation(Section* section);
			~MandelbrotAnimation() = default;
			void set_palette(Colors::RGB *colors, uint8_t num_colors);
			void update();

		private:
			Colors::RGB black_ = {0, 0, 0};

			/// Tracks the number of runs through the Mandelbrot function for each Pixel.
			uint8_t iterations_ = 0;

			/// Maximum number of iterations to run. Defaults to num_colors.
			uint8_t max_iterations_ = 10;

			void map();
	};
}

#endif // MANDELBROTANIMATION_H
