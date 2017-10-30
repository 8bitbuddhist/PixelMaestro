/*
	Colors.cpp - Color handling utilities.
*/

#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

namespace PixelMaestro {
	class Colors {

		private:
		public:
			/// Stores an RGB definition of a color.
			struct RGB {
				/// The color's red value.
				uint8_t r;

				/// The color's green value.
				uint8_t g;

				/// The color's blue value.
				uint8_t b;

				/**
				 * Constructor. Defaults to black if no other parameters are provided.
				 * @param red Red value.
				 * @param green Green value.
				 * @param blue Blue value.
				 */
				RGB(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0) {
					this->r = red;
					this->g = green;
					this->b = blue;
				}

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
						(uint8_t)((r + color_two.r) % 255),
						(uint8_t)((g + color_two.g) % 255),
						(uint8_t)((b + color_two.b) % 255)
					};
				}

				RGB operator-(RGB color_two) {
					return {
						(uint8_t)((r - color_two.r) % 255),
						(uint8_t)((g - color_two.g) % 255),
						(uint8_t)((b - color_two.b) % 255)
					};
				}

				RGB operator*(float multiplier) {
					return {
						(uint8_t)(r * multiplier),
						(uint8_t)(g * multiplier),
						(uint8_t)(b * multiplier)
					};
				}

				RGB operator/(float divisor) {
					return {
						(uint8_t)(r / divisor),
						(uint8_t)(g / divisor),
						(uint8_t)(b / divisor)
					};
				}
			};

			/// Determines the blending algorithm used when mixing two colors.
			enum MixMode : uint8_t {
				/// Do not mix the colors.
				None,

				/// Mixes both colors with a specific blend percentage (blending is applied to the Overlay).
				Alpha,

				/// Multiplies the base color by the overlay color.
				Multiply,

				/// Draws lit Pixels, but treats black Pixels as transparent.
				Overlay
			};

			static RGB generate_random_color();
			static void generate_random_color_array(RGB *array, uint8_t num_colors);
			static void generate_scaling_color_array(RGB* array, RGB* base_color, RGB* target_color, uint8_t num_colors, bool reverse = false);
			static void generate_scaling_color_array(RGB* array, RGB* base_color, uint8_t num_colors, uint8_t threshold, bool reverse = false);
			static RGB mix_colors(RGB color_one, RGB color_two, MixMode mode, uint8_t alpha = 0);
	};
}

#endif // COLORS_H
