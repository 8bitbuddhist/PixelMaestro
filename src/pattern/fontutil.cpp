/*
 * FontUtil.cpp - Tools for utilizing and interacting with fonts.
 */
#include "fontutil.h"
#include "point.h"

namespace PixelMaestro {
	/**
	 * Renders a string in the Frame.
	 * @param frame The Pattern frame that the string will be rendered to.
	 * @param patternSize The size of the Pattern/frame.
	 * @param string The string to render.
	 * @param numChars The length of the string.
	 */
	void FontUtil::printString(Font *font, bool *frame, Point *patternSize, const char *string, int numChars) {
		unsigned char *currentChar;
		Point *fontSize = font->size;

		/*
		 * Indicates where to draw the next letter.
		 * TODO: Add word wrapping by adjusting the y-coordinate.
		 */
		Point cursor = {0, 0};

		for (int letter = 0; letter < numChars; letter++) {
			/*
			 * Each char in the font corresponds to a column.
			 * For each char, iterate over each row of the Pattern.
			 * Use bitmasking to check whether the Pixel should be turned on or off, then move to the next column.
			 * Offset is used because by default, the char is printed upside-down. This inverts it by printing it from the bottom up.
			 */
			currentChar = font->getChar(string[letter]);
			for (int column = 0; column < fontSize->x; column++) {
				for (int row = 0; row < fontSize->y; row++) {
					// Check to make sure we haven't exceeded the bounds of the Pattern
					if (cursor.x + column < patternSize->x && row < fontSize->y) {
						frame[(row * patternSize->x) + (cursor.x + column)] = ((currentChar[column] >> row) & 1);
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
}
