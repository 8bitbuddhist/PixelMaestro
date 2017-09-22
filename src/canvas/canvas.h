/*
 * Canvas - Draws a pattern using the Section's underlying Animation.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "basecanvas.h"

namespace PixelMaestro {
	class Canvas : public BaseCanvas {
		public:
			Canvas(Section* section);
			~Canvas();
			void activate(unsigned int pixel);
			void deactivate(unsigned int pixel);
			Colors::RGB get_pixel_color(unsigned int pixel);
			void initialize_pattern();

		protected:
			/**
				The pattern to display.
				Stored as an array of booleans where 'true' indicates a drawn Pixel.
			*/
			bool* pattern_ = nullptr;
	};
}

#endif // CANVAS_H
