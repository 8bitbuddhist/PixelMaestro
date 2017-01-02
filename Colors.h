/*
	Colors.h - Arduino library for defining commonly used colors and methods

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef COLORS_H
#define COLORS_H

namespace PixelMaestro {
	class Colors {

		private:
		public:
			typedef struct RGB {
				unsigned char r;
				unsigned char g;
				unsigned char b;
			} RGB;

			enum MixMode {
				NORMAL,
				ALPHA_BLENDING
			};

			static RGB RED;
			static RGB GREEN;
			static RGB BLUE;
			static RGB WHITE;
			static RGB BLACK;

			// Extended color set
			static RGB ORANGE;
			static RGB YELLOW;
			static RGB CHARTREUSE;
			static RGB SPRING;
			static RGB CYAN;
			static RGB AZURE;
			static RGB VIOLET;
			static RGB MAGENTA;
			static RGB ROSE;
			static RGB INDIGO;
			static RGB COLORWHEEL[];
			static RGB RAINBOW[];

			static bool colorsMatch(RGB *colorOne, RGB *colorTwo);
			static RGB HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val);
			static void generateRandomColorArray(RGB newArray[], RGB baseColor, unsigned char numColors, float range = 1.0);
			static void generateScalingColorArray(RGB newArray[], RGB baseColor, RGB targetColor, unsigned char numColors, bool reverse = false);
			static void generateScalingColorArray(RGB newArray[], RGB baseColor, unsigned char numColors, unsigned char threshold, bool reverse = false);
			static RGB mixColors(RGB *colorOne, RGB *colorTwo, MixMode mode, float alpha = 0);
	};
}

#endif // COLORS_H
