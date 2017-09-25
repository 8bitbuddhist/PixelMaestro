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

				void operator=(RGB color_two) {
					r = color_two.r;
					g = color_two.g;
					b = color_two.b;
				}

				bool operator==(RGB color_two) {
					return r == color_two.r && g == color_two.g && b == color_two.b;
				}

				bool operator!=(RGB color_two) {
					return !operator==(color_two);
				}

				RGB operator+(RGB color_two) {
					return {
						(unsigned char)((r + color_two.r) % 255),
						(unsigned char)((g + color_two.g) % 255),
						(unsigned char)((b + color_two.b) % 255)
					};
				}

				RGB operator-(RGB color_two) {
					return {
						(unsigned char)((r - color_two.r) % 255),
						(unsigned char)((g - color_two.g) % 255),
						(unsigned char)((b - color_two.b) % 255)
					};
				}

				RGB operator*(float multiplier) {
					return {
						(unsigned char)(r * multiplier),
						(unsigned char)(g * multiplier),
						(unsigned char)(b * multiplier)
					};
				}

				RGB operator/(float divisor) {
					return {
						(unsigned char)(r / divisor),
						(unsigned char)(g / divisor),
						(unsigned char)(b / divisor)
					};
				}
			};

			/// Determines the blending algorithm used when mixing two colors.
			enum MixMode {
				/// Do not mix the colors.
				None,

				/// Mixes both colors with a specific blend percentage (blending is applied to the Overlay).
				Alpha,

				/// Multiplies the base color by the overlay color.
				Multiply,

				/// Draws lit Pixels, but treats black Pixels as transparent.
				Overlay
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

			static RGB generate_random_color();
			static void generate_random_color_array(RGB new_array[], RGB* base_color, unsigned int num_colors, float range = 1.0);
			static void generate_scaling_color_array(RGB new_array[], RGB* base_color, RGB* target_color, unsigned int num_colors, bool reverse = false);
			static void generate_scaling_color_array(RGB new_array[], RGB* base_color, unsigned int num_colors, unsigned char threshold, bool reverse = false);
			static RGB mix_colors(RGB color_one, RGB color_two, MixMode mode, unsigned char alpha = 0);
	};
}

#endif // COLORS_H
