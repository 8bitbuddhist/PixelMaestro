/*
	Colors.cpp - Library for defining commonly used colors and methods for handling those colors.
*/

#include "Colors.h"
#include "Utility.h"

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
	Colors::RGB Colors::generateRandomColor() {
		return RGB {
			(unsigned char)(Utility::rand() % 255),
			(unsigned char)(Utility::rand() % 255),
			(unsigned char)(Utility::rand() % 255)
		};
	}

	/**
		Creates a randomly generated array of colors based off of a base color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param numColors Number of colors to generate.
	*/
	void Colors::generateRandomColorArray(RGB newArray[], RGB *baseColor, unsigned int numColors, float range) {
		for (unsigned int newColorIndex = 0; newColorIndex < numColors; newColorIndex++) {
			newArray[newColorIndex] = {
				(unsigned char)(baseColor->r > 0 ? baseColor->r - (unsigned char)(Utility::rand() % (unsigned char)(baseColor->r * range)) : 0),
				(unsigned char)(baseColor->g > 0 ? baseColor->g - (unsigned char)(Utility::rand() % (unsigned char)(baseColor->g * range)) : 0),
				(unsigned char)(baseColor->b > 0 ? baseColor->b - (unsigned char)(Utility::rand() % (unsigned char)(baseColor->b * range)) : 0)
			};
		}
	}

	/**
		Creates an array of colors that gradually merge from a base color to a target color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param targetColor The target color.
		@param numColors Number of colors in the array.
		@param reverse If true, the second half of the array will event from targetColor back to baseColor.
	*/
	void Colors::generateScalingColorArray(RGB newArray[], RGB *baseColor, RGB *targetColor, unsigned int numColors, bool reverse) {
		if (reverse) {
			numColors /= 2;
		}

		// Calculate the distance between each color.
		signed short step[] = {
			(signed short)((targetColor->r - baseColor->r) / (float)numColors),
			(signed short)((targetColor->g - baseColor->g) / (float)numColors),
			(signed short)((targetColor->b - baseColor->b) / (float)numColors)
		};

		// Apply the step distance to each index of the array.
		for (unsigned int i = 0; i < numColors; i++) {
			newArray[i].r =	baseColor->r + (step[0] * i);
			newArray[i].g = baseColor->g + (step[1] * i);
			newArray[i].b = baseColor->b + (step[2] * i);
		}

		if (reverse) {
			// Handle the middle color.
			newArray[numColors].r = baseColor->r + (step[0] * numColors);
			newArray[numColors].g = baseColor->g + (step[1] * numColors);
			newArray[numColors].b = baseColor->b + (step[2] * numColors);

			// Repeat the first half of the array in reverse for each remaining color.
			for (unsigned int i = numColors + 1; i < (numColors * 2); i++) {
				newArray[i].r = newArray[numColors - (i - numColors)].r;
				newArray[i].g = newArray[numColors - (i - numColors)].g;
				newArray[i].b = newArray[numColors - (i - numColors)].b;
			}
		}
	}

	/**
		Creates an array of colors that gradually merge from a base color to a target color.
		The threshold determines the difference between the target color and the base color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param numColors Number of colors in the array.
		@param threshold The variation between the base color and the newly generated target color.
		@param reverse If true, the array will be doubled to event from baseColor to targetColor, then back to baseColor.
	*/
	void Colors::generateScalingColorArray(RGB newArray[], RGB *baseColor, unsigned int numColors, unsigned char threshold, bool reverse) {
		RGB newColor = {
			(unsigned char)(baseColor->r - threshold),
			(unsigned char)(baseColor->g - threshold),
			(unsigned char)(baseColor->b - threshold)
		};
		generateScalingColorArray(newArray, baseColor, &newColor, numColors, reverse);
	}

	/**
		Mixes two colors.

		@param colorOne The first color to mix.
		@param colorTwo The second color to mix.
		@param mode The type of mixing to perform.
		@param alpha Color two alpha factor.
		@return The mixed color.
	*/
	Colors::RGB Colors::mixColors(RGB *colorOne, RGB *colorTwo, MixMode mode, float alpha) {
		RGB mixedColor;

		switch (mode) {
			case MixMode::NORMAL:
				alpha = 0.5;
				// Fall through to alpha-blending
			case MixMode::ALPHA_BLENDING:
			{
				mixedColor.r = (alpha * colorTwo->r) + ((1 - alpha) * colorOne->r);
				mixedColor.g = (alpha * colorTwo->g) + ((1 - alpha) * colorOne->g);
				mixedColor.b = (alpha * colorTwo->b) + ((1 - alpha) * colorOne->b);
				break;
			}
			case MixMode::MULTIPLY:
			{
				mixedColor.r = colorOne->r * (float)(colorTwo->r / (float)255);
				mixedColor.g = colorOne->g * (float)(colorTwo->g / (float)255);
				mixedColor.b = colorOne->b * (float)(colorTwo->b / (float)255);
				break;
			}
			default:	// Return colorOne
				mixedColor = *colorOne;
				break;
		};

		return mixedColor;
	}
}
