/*
	Colors.cpp - Library for defining commonly used colors and methods for handling those colors.
*/

#include "colors.h"
#include "utility.h"

namespace PixelMaestro {
	// Simple color set
	Colors::RGB Colors::RED 	= {255, 0, 0};
	Colors::RGB Colors::GREEN 	= {0, 255, 0};
	Colors::RGB Colors::BLUE 	= {0, 0, 255};
	Colors::RGB Colors::WHITE 	= {255, 255, 255};
	Colors::RGB Colors::BLACK 	= {0, 0, 0};

	// Extended color set
	Colors::RGB Colors::ORANGE 		= {255, 128, 0};
	Colors::RGB Colors::YELLOW 		= {255, 255, 0};
	Colors::RGB Colors::CHARTREUSE	= {128, 255, 0};
	Colors::RGB Colors::SPRING 		= {0, 255, 128};
	Colors::RGB Colors::CYAN 		= {0, 255, 255};
	Colors::RGB Colors::AZURE 		= {0, 128, 255};
	Colors::RGB Colors::VIOLET 		= {143, 0, 255};
	Colors::RGB Colors::MAGENTA 	= {255, 0, 255};
	Colors::RGB Colors::ROSE 		= {255, 0, 128};
	Colors::RGB Colors::INDIGO 		= {75, 0, 130};

	// Color collections
	Colors::RGB Colors::COLORWHEEL[12] = {
		Colors::RED,
		Colors::ORANGE,
		Colors::YELLOW,
		Colors::CHARTREUSE,
		Colors::GREEN,
		Colors::SPRING,
		Colors::CYAN,
		Colors::AZURE,
		Colors::BLUE,
		Colors::VIOLET,
		Colors::MAGENTA,
		Colors::ROSE
	};
	Colors::RGB Colors::RAINBOW[7] = {
		Colors::RED,
		Colors::ORANGE,
		Colors::YELLOW,
		Colors::GREEN,
		Colors::BLUE,
		Colors::INDIGO,
		Colors::VIOLET
	};

	/**
	 * Creates a random color.
	 * @return Random color.
	 */
	Colors::RGB Colors::generate_random_color() {
		return RGB {
			(unsigned char)(Utility::rand() % 255),
			(unsigned char)(Utility::rand() % 255),
			(unsigned char)(Utility::rand() % 255)
		};
	}

	/**
		Creates a randomly generated array of colors based off of a base color.

		@param new_array Array to populate.
		@param base_color The initial color.
		@param num_colors Number of colors to generate.
	*/
	void Colors::generate_random_color_array(RGB new_array[], RGB* base_color, unsigned int num_colors, float range) {
		for (unsigned int new_color_index = 0; new_color_index < num_colors; new_color_index++) {
			new_array[new_color_index] = {
				(unsigned char)(base_color->r > 0 ? base_color->r - (unsigned char)(Utility::rand() % (unsigned char)(base_color->r * range)) : 0),
				(unsigned char)(base_color->g > 0 ? base_color->g - (unsigned char)(Utility::rand() % (unsigned char)(base_color->g * range)) : 0),
				(unsigned char)(base_color->b > 0 ? base_color->b - (unsigned char)(Utility::rand() % (unsigned char)(base_color->b * range)) : 0)
			};
		}
	}

	/**
		Creates an array of colors that gradually merge from a base color to a target color.

		@param new_array Array to populate.
		@param base_color The initial color.
		@param target_color The target color.
		@param num_colors Number of colors in the array.
		@param reverse If true, the second half of the array will event from target_color back to base_color.
	*/
	void Colors::generate_scaling_color_array(RGB new_array[], RGB* base_color, RGB* target_color, unsigned int num_colors, bool reverse) {
		if (reverse) {
			num_colors /= 2;
		}

		// Calculate the distance between each color.
		signed short step[] = {
			(signed short)((target_color->r - base_color->r) / (float)num_colors),
			(signed short)((target_color->g - base_color->g) / (float)num_colors),
			(signed short)((target_color->b - base_color->b) / (float)num_colors)
		};

		// Apply the step distance to each index of the array.
		for (unsigned int i = 0; i < num_colors; i++) {
			new_array[i].r =	base_color->r + (step[0] * i);
			new_array[i].g = base_color->g + (step[1] * i);
			new_array[i].b = base_color->b + (step[2] * i);
		}

		if (reverse) {
			// Handle the middle color.
			new_array[num_colors].r = base_color->r + (step[0] * num_colors);
			new_array[num_colors].g = base_color->g + (step[1] * num_colors);
			new_array[num_colors].b = base_color->b + (step[2] * num_colors);

			// Repeat the first half of the array in reverse for each remaining color.
			for (unsigned int i = num_colors + 1; i < (num_colors * 2); i++) {
				new_array[i].r = new_array[num_colors - (i - num_colors)].r;
				new_array[i].g = new_array[num_colors - (i - num_colors)].g;
				new_array[i].b = new_array[num_colors - (i - num_colors)].b;
			}
		}
	}

	/**
		Creates an array of colors that gradually merge from a base color to a target color.
		The threshold determines the difference between the target color and the base color.

		@param new_array Array to populate.
		@param base_color The initial color.
		@param num_colors Number of colors in the array.
		@param threshold The variation between the base color and the newly generated target color.
		@param reverse If true, the array will be doubled to event from base_color to target_color, then back to base_color.
	*/
	void Colors::generate_scaling_color_array(RGB new_array[], RGB* base_color, unsigned int num_colors, unsigned char threshold, bool reverse) {
		RGB new_color = {
			(unsigned char)(base_color->r - threshold),
			(unsigned char)(base_color->g - threshold),
			(unsigned char)(base_color->b - threshold)
		};
		generate_scaling_color_array(new_array, base_color, &new_color, num_colors, reverse);
	}

	/**
		Mixes two colors.

		@param color_one The first color to mix.
		@param color_two The second color to mix.
		@param mode The type of mixing to perform.
		@param alpha Color two alpha factor.
		@return The mixed color.
	*/
	Colors::RGB Colors::mix_colors(RGB* color_one, RGB* color_two, MixMode mode, float alpha) {
		RGB mixed_color;

		switch (mode) {
			case MixMode::NORMAL:
				alpha = 0.5;
				// Fall through to alpha-blending
			case MixMode::ALPHA_BLENDING:
			{
				mixed_color.r = (alpha * color_two->r) + ((1 - alpha) * color_one->r);
				mixed_color.g = (alpha * color_two->g) + ((1 - alpha) * color_one->g);
				mixed_color.b = (alpha * color_two->b) + ((1 - alpha) * color_one->b);
				break;
			}
			case MixMode::MULTIPLY:
			{
				mixed_color.r = color_one->r * (float)(color_two->r / (float)255);
				mixed_color.g = color_one->g * (float)(color_two->g / (float)255);
				mixed_color.b = color_one->b * (float)(color_two->b / (float)255);
				break;
			}
			default:	// Return color_one
				mixed_color = *color_one;
				break;
		};

		return mixed_color;
	}
}
