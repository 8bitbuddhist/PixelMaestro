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
			static Colors::RGB RED;
			static Colors::RGB GREEN;
			static Colors::RGB BLUE;
			static Colors::RGB WHITE;
			static Colors::RGB BLACK;

			// Extended color set.
			static Colors::RGB ORANGE;
			static Colors::RGB YELLOW;
			static Colors::RGB CHARTREUSE;
			static Colors::RGB SPRING;
			static Colors::RGB CYAN;
			static Colors::RGB AZURE;
			static Colors::RGB VIOLET;
			static Colors::RGB MAGENTA;
			static Colors::RGB ROSE;
			static Colors::RGB INDIGO;

			// Sample color arrays.
			static Colors::RGB COLORWHEEL[];
			static Colors::RGB RAINBOW[];
	};
}

#endif // COLORPRESETS_H
