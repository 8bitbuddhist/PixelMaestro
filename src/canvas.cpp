/*
 * Canvas.cpp - Utilities for drawing patterns on a Section.
 */

#include "canvas.h"
#include "utility.h"

namespace PixelMaestro {
	/**
	 * Constructor. This also initializes the Canvas' offset to 0.
	 * @param pattern The array containing the Canvas' individual pixels.
	 * @param layout The layout (rows and columns) of the Canvas.
	 * @param numFrames The number of frames in the Canvas.
	 */
	Canvas::Canvas(bool *pattern, Point *dimensions) {
		this->pattern = pattern;
		this->dimensions = dimensions;

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
	void Canvas::drawText(Font *font, const char *text, unsigned int numChars) {
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
						this->pattern[(row * this->dimensions->x) + (cursor.x + column)] = ((currentChar[column] >> row) & 1);
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
	 * Redraw the Canvas.
	 */
	void Canvas::update(const unsigned long &currentTime) {
		/*
		 * Iterate over each bool in the Canvas.
		 * If the bool is false, deactivate the corresponding Pixel in the Pixel grid.
		 * If repeat is enabled, wrap the Canvas to the opposite end of the grid.
		 * If Canvas::offset is set, calculate the true index of the Pixel by adding the offset.
		 */
		for (unsigned short row = 0; row < dimensions->y; row++) {
			for (unsigned short column = 0; column < dimensions->x; column++) {
				// Iterate through disabled Pixels
				if (!pattern[parent_section_->getPixelIndex(row, column)]) {
					if (row + offset->y < parent_section_->getDimensions()->y &&
						column + offset->x < parent_section_->getDimensions()->x) {
						parent_section_->setOne(row + offset->y,
												column + offset->x,
												&Colors::BLACK);
					}
					else if (repeat) {
						parent_section_->setOne((row + offset->y) % parent_section_->getDimensions()->y,
												(column + offset->x) % parent_section_->getDimensions()->x,
												&Colors::BLACK);
					}
				}
			}
		}

		/*
		 * If Canvas::scrollRate is set, scroll the Canvas.
		 * scrollRate dictates how many refreshes will occur before the Canvas is scrolled.
		 * For each axis, determine the impact of scrollRate-><axis> and make the change.
		 * If the axis exceeds the bounds of the Pixel grid, wrap back to the start/end.
		 */
		unsigned long targetTime = currentTime - last_scroll;
		if (scroll_interval) {
			if (scroll_interval->x != 0 && (Utility::abs(scroll_interval->x) * parent_section_->getRefreshRate()) <= targetTime) {

				// Increment or decrement the offset depending on the scroll direction.
				if (scroll_interval->x > 0) {
					offset->x++;
				}
				else {
					offset->x--;
				}

				// Check the bounds of the parent Section.
				if (offset->x >= parent_section_->getDimensions()->x) {
					offset->x = 0;
				}
				else if (offset->x - 1 < 0) {
					offset->x = parent_section_->getDimensions()->x;
				}
				last_scroll = currentTime;
			}

			if (scroll_interval->y != 0 && (Utility::abs(scroll_interval->y) * parent_section_->getRefreshRate()) <= targetTime) {

				// Increment or decrement the offset depending on the scroll direction.
				if (scroll_interval->y > 0) {
					offset->y++;
				}
				else {
					offset->y--;
				}

				// Check the bounds of the parent Section.
				if (offset->y >= parent_section_->getDimensions()->y) {
					offset->y = 0;
				}
				else if (offset->y - 1 < 0) {
					offset->y = parent_section_->getDimensions()->y;
				}

				// Check to see if lastScroll was already set by scrollRate->x
				if (last_scroll != currentTime) {
					last_scroll = currentTime;
				}
			}
		}
	}

	Canvas::~Canvas() {
		delete this->offset;
	}
}
