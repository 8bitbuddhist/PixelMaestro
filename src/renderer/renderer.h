/*
 * Renderer - Renders Section output to a device.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "../core/section.h"

namespace PixelMaestro {
	class Renderer {
		public:
			/// Defines the method of writing to the device.
			enum Methods {
				/// Writes Pixel values by column first.
				COLUMN_AND_ROW,

				/// Writes Pixel values by row first.
				ROW_AND_COLUMN,

				/// Writes each Pixel value in sequential order.
				SEQUENTIAL
			};

			Renderer(Section* section, Methods method);
			virtual void update() = 0;

		private:
			Renderer::Methods method_;
			Section* section_;
	};
}

#endif // RENDERER_H
