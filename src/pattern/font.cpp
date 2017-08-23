#include "fonts/font5x8.h"
#include "font.h"

namespace PixelMaestro {
	void Font::printChars(bool *frame, Section::Layout *patternLayout, const char *string, int numChars) {
		int startCol = 0;
		Section::Layout *fontLayout = new Section::Layout(8, 5);

		for (int letter = 0; letter < numChars; letter++) {
			/*
			 * Each char in the font corresponds to a column.
			 * For each char, iterate over each row of the Pattern.
			 * Use bitmasking to check whether the Pixel should be turned on or off, then move to the next column.
			 * Offset is used because by default, the char is printed upside-down. This inverts it by printing it from the bottom up.
			 */
			for (int column = 0; column < fontLayout->columns; column++) {
				for (int row = 0; row < fontLayout->rows; row++) {
					// Check to make sure we haven't exceeded the bounds of the Pattern
					if (startCol + column < patternLayout->columns && row < patternLayout->rows) {
						frame[(row * patternLayout->columns) + (startCol + column)] = ((font5x8[string[letter] - 32][column] >> row) & 1);
					}
					else {
						break;
					}
				}
			}
			// Add 1 to startCol to add space between letters
			startCol += (fontLayout->columns);
		}
	}
}
