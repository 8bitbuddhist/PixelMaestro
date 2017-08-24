/*
 * Canvas.h - Utilities for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "canvas/fonts/font.h"
#include "point.h"
#include "section.h"

namespace PixelMaestro {
	class Section;

	class Canvas {
		public:
			/// The size of the Canvas.
			Point *dimensions = nullptr;

			/// How far the Canvas is offset from the Pixel grid origin (where the origin is the first Pixel in the grid).
			/// TODO: Remove this and instead make it a required parameter for each Canvas::draw() method.
			Point *offset = nullptr;

			Section *parent_section_ = nullptr;

			/**
				The pattern to display.
				Stored as an array of booleans where 1 indicates an active Pixel.
				TODO: Use the Pixel array directly.
			*/
			bool *pattern = nullptr;

			/// Whether to repeat the Pattern over the grid (requires scrollRate to be set).
			bool repeat = false;

			/**
			 * Direction and rate to scroll the Canvas.
			 * Scrolling occurs on every cycle update.
			 * Setting an axis to 0 (default) disables scrolling on that axis.
			 */
			Point *scrollRate = nullptr;

			Canvas(bool *pattern, Point *dimensions);
			void drawText(Font *font, const char *text, unsigned int numChars);
			~Canvas();			
	};
}

#endif // CANVAS_H
