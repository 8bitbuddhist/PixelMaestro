/*
	Colors.cpp - Arduino library for defining commonly used colors and methods

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

#include "Colors.h"
#include <math.h>
#include <stdlib.h>

namespace PixelMaestro {
	Colors::RGB Colors::RED = {255, 0, 0};
	Colors::RGB Colors::GREEN = {0, 255, 0};
	Colors::RGB Colors::BLUE = {0, 0, 255};
	Colors::RGB Colors::WHITE = {255, 255, 255};
	Colors::RGB Colors::BLACK = {0, 0, 0};

	// Extended color set
	Colors::RGB Colors::ORANGE = {255, 128, 0};
	Colors::RGB Colors::YELLOW = {255, 255, 0};
	Colors::RGB Colors::CHARTREUSE = {128, 255, 0};
	Colors::RGB Colors::SPRING = {0, 255, 128};
	Colors::RGB Colors::CYAN = {0, 255, 255};
	Colors::RGB Colors::AZURE = {0, 128, 255};
	Colors::RGB Colors::VIOLET = {143, 0, 255};
	Colors::RGB Colors::MAGENTA = {255, 0, 255};
	Colors::RGB Colors::ROSE = {255, 0, 128};
	Colors::RGB Colors::INDIGO = {180, 0, 130};
	Colors::RGB Colors::COLORWHEEL[] = {
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
	Colors::RGB Colors::RAINBOW[] = {
		Colors::RED,
		Colors::ORANGE,
		Colors::YELLOW,
		Colors::GREEN,
		Colors::BLUE,
		Colors::INDIGO,
		Colors::VIOLET
	};

	/**
		Checks if the current color matches the next color stored.

		@param colorOne First color to match.
		@param colorTwo Second color to match.
		@return True if both colors match.
	*/
	bool Colors::colorsMatch(RGB *colorOne, RGB *colorTwo) {
		return (colorOne->r == colorTwo->r &&
				colorOne->g == colorTwo->g &&
				colorOne->b == colorTwo->b);
	}

	/**
		Converts an HSV value to an RGB value.
		Courtesy of Elco Jacobs' ShiftPWM library (http://www.elcojacobs.com/shiftpwm/)

		@param hue The initial hue.
		@param sat The initial saturation.
		@param val The initial value.
	*/
	Colors::RGB Colors::HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val){
		unsigned char r,g,b;
		unsigned int H_accent = hue/60;
		unsigned int bottom = ((255 - sat) * val)>>8;
		unsigned int top = val;
		unsigned char rising  = ((top-bottom)  *(hue%60   )  )  /  60  +  bottom;
		unsigned char falling = ((top-bottom)  *(60-hue%60)  )  /  60  +  bottom;

		switch(H_accent) {
		case 0:
			r = top;
			g = rising;
			b = bottom;
			break;

		case 1:
			r = falling;
			g = top;
			b = bottom;
			break;

		case 2:
			r = bottom;
			g = top;
			b = rising;
			break;

		case 3:
			r = bottom;
			g = falling;
			b = top;
			break;

		case 4:
			r = rising;
			g = bottom;
			b = top;
			break;

		case 5:
			r = top;
			g = bottom;
			b = falling;
			break;
		}
		Colors::RGB newColor;
		newColor.r = r;
		newColor.g = g;
		newColor.b = b;
		return newColor;
	};

	/**
		Creates a randomly generated array of colors based off of a base color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param numColors Number of colors to generate.
	*/
	void Colors::generateRandomColorArray(Colors::RGB newArray[], Colors::RGB baseColor, unsigned char numColors, float range) {
		for (int newColorIndex = 0; newColorIndex < numColors; newColorIndex++) {
			newArray[newColorIndex].r = baseColor.r - (rand() % (int)(baseColor.r * range));
			newArray[newColorIndex].g = baseColor.g - (rand() % (int)(baseColor.g * range));
			newArray[newColorIndex].b = baseColor.b - (rand() % (int)(baseColor.b * range));
		}
	}

	/**
		Creates an array of colors that gradually merge from a base color to a target color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param targetColor The target color.
		@param numColors Number of colors in the array.
		@param reverse If true, the second half of the array will transition from targetColor back to baseColor.
	*/
	void Colors::generateScalingColorArray(RGB newArray[], RGB baseColor, RGB targetColor, unsigned char numColors, bool reverse) {
		if (reverse) {
			numColors /= 2;
		}

		unsigned char step[] = {
			(unsigned char)ceil((targetColor.r - baseColor.r) / numColors),
			(unsigned char)ceil((targetColor.g - baseColor.g) / numColors),
			(unsigned char)ceil((targetColor.b - baseColor.b) / numColors)
		};

		for (int i = 0; i < numColors; i++) {
			newArray[i].r =	baseColor.r + (step[0] * i);
			newArray[i].g = baseColor.g + (step[1] * i);
			newArray[i].b = baseColor.b + (step[2] * i);
		}

		if (reverse) {
			unsigned char colorIndex = numColors;
			for (int i = numColors; i < (numColors * 2); i++) {
				newArray[i].r =	targetColor.r + (step[0] * colorIndex);
				newArray[i].g = targetColor.g + (step[1] * colorIndex);
				newArray[i].b = targetColor.b + (step[2] * colorIndex);

				colorIndex--;
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
		@param reverse If true, the array will be doubled to transition from baseColor to targetColor, then back to baseColor.
	*/
	void Colors::generateScalingColorArray(RGB newArray[], RGB baseColor, unsigned char numColors, unsigned char threshold, bool reverse) {
		RGB newColor = {(unsigned char)(baseColor.r - threshold),
			(unsigned char)(baseColor.g - threshold),
			(unsigned char)(baseColor.b - threshold)
		};
		generateScalingColorArray(newArray, baseColor, newColor, numColors, reverse);
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
		Colors::RGB mixedColor;

		switch (mode) {
			case MixMode::ALPHA_BLENDING:
			{
				mixedColor.r = (alpha * colorTwo->r) + ((1 - alpha) * colorOne->r);
				mixedColor.g = (alpha * colorTwo->g) + ((1 - alpha) * colorOne->g);
				mixedColor.b = (alpha * colorTwo->b) + ((1 - alpha) * colorOne->b);
				break;
			}
			default:	// Normal blending
			{
				mixedColor.r = (colorOne->r + colorTwo->r) / 2;
				mixedColor.g = (colorOne->g + colorTwo->g) / 2;
				mixedColor.b = (colorOne->b + colorTwo->b) / 2;
			}
		};

		return mixedColor;
	}
}
