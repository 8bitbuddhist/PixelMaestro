/*
	Colors.cpp - Library for defining commonly used colors and methods for handling those colors.
*/

#ifndef COLORS_H
#define COLORS_H

namespace PixelMaestro {
	class Colors {

		private:
		public:
			/// Stores an RGB definition of a color.
			struct RGB {
				/// The color's red value.
				unsigned char r;

				/// The color's green value.
				unsigned char g;

				/// The color's blue value.
				unsigned char b;

				void operator=(RGB colorTwo) {
					r = colorTwo.r;
					g = colorTwo.g;
					b = colorTwo.b;
				}

				bool operator==(RGB colorTwo) {
					return r == colorTwo.r && g == colorTwo.g && b == colorTwo.b;
				}

				bool operator!=(RGB colorTwo) {
					return !operator==(colorTwo);
				}

				RGB operator+(RGB colorTwo) {
					return {
						(unsigned char)((r + colorTwo.r) % 255),
						(unsigned char)((g + colorTwo.g) % 255),
						(unsigned char)((b + colorTwo.b) % 255)
					};
				}

				RGB operator-(RGB colorTwo) {
					return {
						(unsigned char)((r - colorTwo.r) % 255),
						(unsigned char)((g - colorTwo.g) % 255),
						(unsigned char)((b - colorTwo.b) % 255)
					};
				}
			};

			/// Determines the blending algorithm used when mixing two colors.
			enum MixMode {
				/// Do not mix the colors.
				NONE,

				/// Simple 50/50 blending.
				NORMAL,

				/// Mixes both colors with a specific blend percentage (blending is applied to the Overlay).
				ALPHA_BLENDING,

				/// Multiplies the base color by the overlay color.
				MULTIPLY
			};

			// Basic color set.
			static RGB RED;
			static RGB GREEN;
			static RGB BLUE;
			static RGB WHITE;
			static RGB BLACK;

			// Extended color set.
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

			// Sample color arrays.
			static RGB COLORWHEEL[];
			static RGB RAINBOW[];

			static RGB HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val);
			static void generateRandomColorArray(RGB newArray[], RGB baseColor, unsigned int numColors, float range = 1.0);
			static void generateScalingColorArray(RGB newArray[], RGB baseColor, RGB targetColor, unsigned int numColors, bool reverse = false);
			static void generateScalingColorArray(RGB newArray[], RGB baseColor, unsigned int numColors, unsigned char threshold, bool reverse = false);
			static RGB mixColors(RGB *colorOne, RGB *colorTwo, MixMode mode, float alpha = 0);
	};
}

#endif // COLORS_H
