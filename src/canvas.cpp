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
	 * Draws a single character.
	 * @param origin The starting coordinates.
	 * @param font The Font to render the text in.
	 * @param character The character to display.
	 */
	void Canvas::drawChar(Point *origin, Font *font, const char character) {
		/*
		 * Each char in the font corresponds to a column.
		 * Each bit in the char corresponds to an individual pixel.
		 * We use bitmasking to get the bit value, then enable/disable the pixel based on that bit.
		 */
		unsigned char *currentChar = font->getChar(character);
		for (int column = 0; column < font->size->x; column++) {
			for (int row = 0; row < font->size->y; row++) {
				// Check to make sure we haven't exceeded the bounds of the Pattern
				if ((origin->x + column < this->dimensions->x) && (origin->y + row < this->dimensions->y)) {
					this->pattern[((origin->y + row) * this->dimensions->x) + (origin->x + column)] = ((currentChar[column] >> row) & 1);
				}
				else {
					break;
				}
			}
		}
	}

	void Canvas::drawLine(Point *origin, Point *target) {
		// Calculate slope
		float slope;
		if (target->x - origin->x == 0) {
			slope = target->y - origin->y;
		}
		else {
			slope = (target->y - origin->y) / (float)(target->x - origin->x);
		}

		Point cursor = { origin->x, origin->y };
		float y_intercept = Utility::abs_float((slope * origin->x) - origin->y);

		/*
		 * Move the cursor along the x-axis.
		 * For each x-coordinate, apply the slope and round the y-value to the nearest integer.
		 */
		while (cursor.x <= target->x) {
			// Make sure we're still in bounds
			if ((cursor.x < this->dimensions->x) && (cursor.y < this->dimensions->y)) {
				this->pattern[(cursor.y * this->dimensions->x) + cursor.x] = 1;
			}

			cursor.x++;
			cursor.y = (slope * (float)cursor.x) + y_intercept;
		}
	}

	/**
	 * Draws a rectangle.
	 * @param origin The starting coordinates.
	 * @param size The size of the rectangle.
	 * @param fill Whether to fill the rectangle or leave it empty
	 */
	void Canvas::drawRect(Point *origin, Point *size, bool fill) {
		Point cursor = { origin->x, origin->y };
		for (int column = 0; column < size->x; column++) {
			// (Re-)Initialize cursor coordinates.
			cursor.x = origin->x + column;
			cursor.y = origin->y;
			for (int row = 0; row < size->y; row++) {
				cursor.y = origin->y + row;
				if ((cursor.x < this->dimensions->x) && (cursor.y < this->dimensions->y)) {
					// Check whether to fill
					if (fill) {
						this->pattern[(cursor.y * this->dimensions->x) + cursor.x] = 1;
					}
					else {
						/*
						 * Only draw if the cursor is at the border of the rectangle.
						 * We do this by checking to see if the cursor is either horizontally or vertically aligned with the starting or end point.
						 */
						if ((cursor.x == origin->x || cursor.y == origin->y) ||
							(column == size->x - 1 || row == size->y - 1)) {
							this->pattern[(cursor.y * this->dimensions->x) + cursor.x] = 1;
						}
						else {
							// Don't fill.
							continue;
						}
					}
				}
			}
		}
	}

	/**
	 * Draws a string of characters.
	 * @param origin The starting point for the string.
	 * @param font The Font to render the text in.
	 * @param text The string to render.
	 * @param numChars The number of characters in the string.
	 */
	void Canvas::drawText(Point *origin, Font *font, const char *text, unsigned int numChars) {
		Point cursor = {origin->x, origin->y};

		// Iterate over each letter and draw using drawChar().
		for (unsigned int letter = 0; letter < numChars; letter++) {
			this->drawChar(&cursor, font, text[letter]);

			// Move cursor to the location of the next letter based on the font size.
			cursor.x += font->size->x;
		}
	}

	/**
	 * Redraw the Canvas.
	 * @param currentTime The program's current runtime (normally passed by a Section).
	 */
	void Canvas::update(const unsigned long &currentTime) {
		// Temporarily store the current color being applied.
		Colors::RGB *tmpColor;

		/*
		 * Iterate over each bool in the Canvas.
		 * If the bool is false, deactivate the corresponding Pixel in the Pixel grid.
		 * If repeat is enabled, wrap the out-of-bounds part of the Canvas to the opposite end.
		 * If Canvas::offset is set, calculate the true index of the Pixel by adding the offset.
		 */
		for (unsigned short row = 0; row < dimensions->y; row++) {
			for (unsigned short column = 0; column < dimensions->x; column++) {

				// Iterate through all Pixels. If the Pixel is enabled, assign it the foreground color, otherwise assign the background color.
				// Iterate through disabled Pixels
				if (pattern[parent_section_->getPixelIndex(row, column)]) {
					if (fg_color) {
						tmpColor = fg_color;
					}
					else {
						// Skip this Pixel. This allows the colors already generated by the Section to "pass through" and display.
						continue;
					}

				}
				else {
					if (bg_color) {
						tmpColor = bg_color;
					}
					else {
						tmpColor = &Colors::BLACK;
					}
				}

				if (row + offset->y < parent_section_->getDimensions()->y &&
					column + offset->x < parent_section_->getDimensions()->x) {
					parent_section_->setOne(row + offset->y,
											column + offset->x,
											tmpColor);
				}
				else if (repeat) {
					parent_section_->setOne((row + offset->y) % parent_section_->getDimensions()->y,
											(column + offset->x) % parent_section_->getDimensions()->x,
											tmpColor);
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
			if (scroll_interval->x != 0 && (Utility::abs_int(scroll_interval->x) * parent_section_->getRefreshRate()) <= targetTime) {

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

			if (scroll_interval->y != 0 && (Utility::abs_int(scroll_interval->y) * parent_section_->getRefreshRate()) <= targetTime) {

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

				last_scroll = currentTime;
			}
		}
	}

	Canvas::~Canvas() {
		delete this->offset;
	}
}
