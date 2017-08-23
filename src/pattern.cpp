/*
 * Pattern.cpp - Defines a Pattern to display in a Section.
 */

#include "pattern.h"

namespace PixelMaestro {
	/**
	 * Constructor. This also initializes the Pattern's offset to 0.
	 * @param pattern The array containing the full pattern.
	 * @param layout The layout (rows and columns) of the Pattern.
	 * @param numFrames The number of frames in the Pattern.
	 */
	Pattern::Pattern(bool **pattern, Point *dimensions, unsigned short numFrames) {
		this->pattern = pattern;
		this->dimensions = dimensions;
		this->frames = numFrames;

		// Initial offset is set to 0
		this->offset = new Point(0, 0);
	}

	/**
	 * Renders text in the specified frame.
	 * @param font The Font to use when rendering the text.
	 * @param frame The Pattern frame that the text will be rendered in.
	 * @param text The string to render.
	 * @param numChars The number of characters in the string.
	 */
	void Pattern::drawText(Font *font, int frame, const char *text, unsigned int numChars) {
		unsigned char *currentChar;
		Point *fontSize = font->size;

		/*
		 * Indicates where to draw the next letter.
		 * TODO: Add word wrapping by adjusting the y-coordinate.
		 */
		Point cursor = {0, 0};

		for (unsigned int letter = 0; letter < numChars; letter++) {
			/*
			 * Each char in the font corresponds to a column.
			 * For each char, iterate over each row of the Pattern.
			 * Use bitmasking to check whether the Pixel should be turned on or off, then move to the next column.
			 * Offset is used because by default, the char is printed upside-down. This inverts it by printing it from the bottom up.
			 */
			currentChar = font->getChar(text[letter]);
			for (int column = 0; column < fontSize->x; column++) {
				for (int row = 0; row < fontSize->y; row++) {
					// Check to make sure we haven't exceeded the bounds of the Pattern
					if (cursor.x + column < this->dimensions->x && row < fontSize->y) {
						this->pattern[frame][(row * this->dimensions->x) + (cursor.x + column)] = ((currentChar[column] >> row) & 1);
					}
					else {
						break;
					}
				}
			}
			// Move cursor to the location of the next letter.
			cursor.x += fontSize->x;
		}
	}

	Pattern::~Pattern() {
		delete this->offset;
	}
}
