/*
 * Canvas.cpp - Utilities for drawing patterns on a Section.
 */

#include "canvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. This also initializes the Canvas' offset to 0.
	 * @param pattern The array containing the Canvas' individual pixels.
	 * @param layout The layout (rows and columns) of the Canvas.
	 * @param numFrames The number of frames in the Canvas.
	 */
	Canvas::Canvas(bool **pattern, Point *dimensions, unsigned short numFrames) {
		this->pattern = pattern;
		this->dimensions = dimensions;
		this->frames = numFrames;

		// Initial offset is set to 0
		this->offset = new Point(0, 0);
	}

	/**
	 * Draws text in the Canvas.
	 * @param font The Font to use when rendering the text.
	 * @param frame The frame that the text will be rendered in.
	 * @param text The string to render.
	 * @param numChars The number of characters in the string.
	 */
	void Canvas::drawText(Font *font, int frame, const char *text, unsigned int numChars) {
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
			 * Each bit in the char corresponds to an individual pixel.
			 * We use bitmasking to get the bit value, then enable/disable the pixel based on that bit.
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

	/**
	 * Updates the Canvas' cycle index by comparing it to the number of frames.
	 * @param cycleIndex Address of the index tracker (provided by a Section).
	 */
	void Canvas::updateCycle(unsigned short &cycleIndex) {
		cycleIndex++;
		if (cycleIndex == this->frames) {
			cycleIndex = 0;
		}
	}

	Canvas::~Canvas() {
		delete this->offset;
	}
}
