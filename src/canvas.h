/*
 * Canvas.h - Utilities for drawing patterns on a Section.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "canvas/fonts/font.h"
#include "point.h"

namespace PixelMaestro {
	class Canvas {
		public:
			/// The size of the Canvas.
			Point *dimensions = nullptr;

			/// The number of frames in the Canvas.
			unsigned short frames;

			/// The amount of time (in ms) since the last frame change.
			unsigned long last_cycle = 0;

			/// How far the Canvas is offset from the Pixel grid origin (where the origin is the first Pixel in the grid).
			/// TODO: Remove this and instead make it a required parameter for each Canvas::draw() method.
			Point *offset = nullptr;

			/**
				The pattern to display.
				Stored as an array of bool arrays where each bool array is a separate frame.
				TODO: Use the Pixel array directly.
			*/
			bool **pattern = nullptr;

			/// Whether to repeat the Pattern over the grid (requires scrollRate to be set).
			bool repeat = false;

			/**
			 * Direction and rate to scroll the Canvas.
			 * Scrolling occurs on every cycle update.
			 * Setting an axis to 0 (default) disables scrolling on that axis.
			 */
			Point *scrollRate = nullptr;

			Canvas(bool **pattern, Point *dimensions, unsigned short numFrames);
			void drawText(Font *font, int frame, const char *text, unsigned int numChars);
			void updateCycle(unsigned short &cycleIndex);
			~Canvas();
	};
}

#endif // CANVAS_H
