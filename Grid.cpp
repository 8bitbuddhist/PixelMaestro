/*
	Grid.cpp - Library for controlling multiple lines of pixels.
	Requires Line library.

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

#include "Grid.h"
#include "Line.h"

namespace PixelMaestro {
	/**
		Default constructor.
		Note that if you use the default constructor, you MUST use setPixels() to initialize the Pixel array.
	*/
	Grid::Grid() {}

	/**
		Constructor. A Grid is a collection of already initialized Lines.
		Grids have their own wrapper functions for speed, animations, etc, although each line can still be managed independently.

		@param arrays Array of Lines.
		@param numArrays Number of Lines to manage.
	*/
	Grid::Grid(Line *lines, unsigned char numLines) {
		setLines(lines, numLines);
	}

	/**
		Returns the Line at the specified index.

		@param array Index of the array.
		@return Line object for the specified array.
	*/
	Line *Grid::getLine(unsigned char row) {
		return &lines_[row];
	}

	/**
		Returns the number of Lines.

		@return Number of Lines.
	*/
	unsigned char Grid::getNumLines() {
		return num_lines_;
	}

	/**
		Sets the color animation used in the Grid.
		Grids have their own animation set, although this is merely a wrapper for individual Line animations.

		@param animation The animation to use.
		@param reverseAnimation Whether to reverse the animation.
	*/
	void Grid::setColorAnimation(Grid::ColorAnimations animation, bool reverseAnimation) {
		// If animation was supplied, change to the desired animation.
		// Otherwise, increment the current animation to the next one.
		if (animation) {
			color_animation_ = animation;
		}
		else {
			unsigned char animationNum = color_animation_ + 1;

			if (animationNum > Grid::ColorAnimations::STRIPES) {
				animationNum = Grid::ColorAnimations::SOLID;
			}

			color_animation_ = Grid::ColorAnimations(animationNum);
		}

		// Iterate through each animation and update each Line as needed.
		for (unsigned char line = 0; line < num_lines_; line++) {
			switch (color_animation_) {
				case Grid::ColorAnimations::STRIPES:
					{
						if (line % 2 == 0) {
							lines_[line].setColorAnimation(Line::ColorAnimations::WAVE, reverseAnimation);
						}
						else {
							lines_[line].setColorAnimation(Line::ColorAnimations::WAVE, !reverseAnimation);
						}
						break;

					}
				case Grid::ColorAnimations::BLINK:
					lines_[line].setColorAnimation(Line::ColorAnimations::BLINK);
					break;
				case Grid::ColorAnimations::SOLID:
					lines_[line].setColorAnimation(Line::ColorAnimations::SOLID);
					break;
				case Grid::ColorAnimations::NONE:
					lines_[line].setColorAnimation(Line::ColorAnimations::NONE);
					break;
				default:
					break;
			}
        }
	}

	/**
		Sets the colors used for each line.

		@param colors Array of colors.
		@param numColors Number of colors in the array.
	*/
	void Grid::setColors(Colors::RGB *colors, unsigned char numColors) {
		for (unsigned char line = 0; line < num_lines_; line++) {
			lines_[line].setColors(colors, numColors);
		}
	}

	/**
		Sets the Lines used in the Grid.

		@param lines Array of Lines.
		@param numLines Number of Lines in the array.
	*/
	void Grid::setLines(Line *lines, unsigned char numLines) {
		lines_ = lines;
		num_lines_ = numLines;
	}

	/**
		Sets the Pixels to use in the Grid.
		This is a convenient alternative to setting Pixels for each Line, as it evenly distributes an array of Pixels across each Line in the Grid.
		This assumes that the Grid already has Lines set with the correct number of pixels per Line.

		@param pixels Array of Pixels.
		@param pixelsPerLine Number of Pixels to set per Line.
	*/
	void Grid::setPixels(Pixel *pixels, unsigned char pixelsPerLine) {
		for (unsigned char line = 0; line < num_lines_; line++) {
			lines_[line].setPixels(&pixels[line * pixelsPerLine], pixelsPerLine);
		}
	}

	/**
		Sets the speed for the active animation for all Lines.

		@param speed Delay between individual animation steps.
		@param delay Delay between complete animation cycles.
	*/
	void Grid::setUpdateSpeed(unsigned char speed, unsigned char delay) {
		for (unsigned char line = 0; line < num_lines_; line++) {
			lines_[line].setUpdateSpeed(speed, delay);
		}
	}

	/**
		Toggles fading for all Lines.
	*/
	void Grid::toggleFade() {
		for (unsigned char line = 0; line < num_lines_; line++) {
			lines_[line].toggleFade();
		}
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Grid::update(unsigned long currentTime) {
		// Update each array
		for (unsigned char row = 0; row < num_lines_; row++) {
			lines_[row].update(currentTime);
		}
	}
}
