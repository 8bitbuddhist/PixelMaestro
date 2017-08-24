/*
 * Canvas.h - Utilities for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "canvas/fonts/font.h"
#include "colors.h"
#include "point.h"
#include "section.h"

namespace PixelMaestro {
	class Section;

	class Canvas {
		public:

			/// The background color of the Canvas.
			Colors::RGB *bg_color = nullptr;

			/// The size of the Canvas.
			Point *dimensions = nullptr;

			/// The foregound color of the Canvas.
			Colors::RGB *fg_color = nullptr;

			/// How far the Canvas is offset from the Pixel grid origin (where the origin is the first Pixel in the grid).
			/// TODO: Remove this and instead make it a required parameter for each Canvas::draw() method.
			Point *offset = nullptr;

			/// The Canvas' parent Section. This is automatically set after using Section::setCanvas().
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
			Point *scroll_interval = nullptr;

			/// The last time the Canvas scrolled.
			unsigned long last_scroll = 0;

			Canvas(bool *pattern, Point *dimensions);
			void drawChar(Font *font, const char *character);
			void drawRect(Point *origin, Point *size);
			void drawText(Point *origin, Font *font, const char *text, unsigned int numChars);
			void update(const unsigned long &currentTime);
			~Canvas();			
	};
}

#endif // CANVAS_H
