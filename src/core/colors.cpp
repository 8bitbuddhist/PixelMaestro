/*
	Colors.cpp - Color handling utilities.
*/

#include "../utility.h"
#include "colors.h"

namespace PixelMaestro {
	/**
	 * Creates a random color.
	 * @return Random color.
	 */
	Colors::RGB Colors::generate_random_color() {
		return RGB {
			(uint8_t)(Utility::rand(255)),
			(uint8_t)(Utility::rand(255)),
			(uint8_t)(Utility::rand(255))
		};
	}

	/**
	 * Creates a randomly generated array of colors.
	 * @param array The array to populate.
	 * @param num_colors The number of colors to generate.
	 */
	void Colors::generate_random_color_array(RGB* array, uint8_t num_colors) {
		for (uint8_t i = 0; i < num_colors; i++) {
			array[i] = generate_random_color();
		}
	}

	/**
		Creates an array of colors that gradually blend from a base color to a target color.

		@param array The array to populate.
		@param base_color The initial color.
		@param target_color The target color.
		@param num_colors Number of colors in the array.
		@param reverse If true, the array will be mirrored from the target color back to the base color.
	*/
	void Colors::generate_scaling_color_array(RGB* array, RGB* base_color, RGB* target_color, uint8_t num_colors, bool reverse) {
		if (reverse) {
			num_colors /= 2;
		}

		// Calculate the distance between each color.
		int16_t step[] = {
			(int16_t)((target_color->r - base_color->r) / (float)num_colors),
			(int16_t)((target_color->g - base_color->g) / (float)num_colors),
			(int16_t)((target_color->b - base_color->b) / (float)num_colors)
		};

		// Apply the step distance to each index of the array.
		for (uint8_t i = 0; i < num_colors; i++) {
			array[i].r = base_color->r + (step[0] * i);
			array[i].g = base_color->g + (step[1] * i);
			array[i].b = base_color->b + (step[2] * i);
		}

		if (reverse) {
			// Handle the middle color.
			array[num_colors].r = base_color->r + (step[0] * num_colors);
			array[num_colors].g = base_color->g + (step[1] * num_colors);
			array[num_colors].b = base_color->b + (step[2] * num_colors);

			// Repeat the first half of the array in reverse for each remaining color.
			for (uint8_t i = num_colors + 1; i < (num_colors * 2) + 1; i++) {
				array[i].r = array[num_colors - (i - num_colors)].r;
				array[i].g = array[num_colors - (i - num_colors)].g;
				array[i].b = array[num_colors - (i - num_colors)].b;
			}
		}

		// Handle odd number of colors
		if (num_colors % 2 != 0) {
			if (reverse) {
				//array[(num_colors * 2) + 1] = *base_color;
				array[num_colors * 2] = *base_color;
			}
			else {
				//array[(num_colors * 2) + 1] = *target_color;
				array[num_colors * 2] = *target_color;
			}
		}
	}

	/**
		Mixes two colors.

		@param color_one The first color to mix.
		@param color_two The second color to mix.
		@param mode The type of mixing to perform.
		@param alpha Color two alpha factor (0 - 255).
		@return The mixed color.
	*/
	Colors::RGB Colors::mix_colors(RGB color_one, RGB color_two, MixMode mode, uint8_t alpha) {
		RGB mixed_color;

		switch (mode) {
			case MixMode::Alpha:
			{
				float alpha_pct = alpha / (float)255;
				float alpha_pct_inv = 1 - alpha_pct;
				mixed_color.r = (alpha_pct * color_two.r) + (alpha_pct_inv * color_one.r);
				mixed_color.g = (alpha_pct * color_two.g) + (alpha_pct_inv * color_one.g);
				mixed_color.b = (alpha_pct * color_two.b) + (alpha_pct_inv * color_one.b);
				break;
			}
			case MixMode::Multiply:
			{
				mixed_color.r = color_one.r * (float)(color_two.r / (float)255);
				mixed_color.g = color_one.g * (float)(color_two.g / (float)255);
				mixed_color.b = color_one.b * (float)(color_two.b / (float)255);
				break;
			}
			case MixMode::Overlay:
			{
				if (color_two != Colors::RGB {0, 0, 0}) {
					mixed_color = color_two;
				}
				else {
					mixed_color = color_one;
				}
				break;
			}
			default:	// Return color_one
				mixed_color = color_one;
				break;
		};

		return mixed_color;
	}
}
