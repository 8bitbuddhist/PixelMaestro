/*
 * ColorPresets - Provides pre-defined colors and color palettes.
 */

#ifndef COLORPRESETS_H
#define COLORPRESETS_H

#include "core/colors.h"

namespace PixelMaestro {
	class ColorPresets {
		public:
			// Basic color set.
			static Colors::RGB Red;
			static Colors::RGB Green;
			static Colors::RGB Blue;
			static Colors::RGB White;
			static Colors::RGB Black;

			// Extended color set.
			static Colors::RGB Orange;
			static Colors::RGB Yellow;
			static Colors::RGB Chartreuse;
			static Colors::RGB Spring;
			static Colors::RGB Cyan;
			static Colors::RGB Azure;
			static Colors::RGB Violet;
			static Colors::RGB Magenta;
			static Colors::RGB Rose;
			static Colors::RGB Indigo;

			// Sample color arrays.
			static Colors::RGB Colorwheel[];
			static Colors::RGB Rainbow[];
	};
}

#endif // COLORPRESETS_H
