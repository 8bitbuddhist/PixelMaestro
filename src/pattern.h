/*
 * Pattern.h - Defines a Pattern to display in a Section.
 */

#ifndef PATTERN_H
#define PATTERN_H

#include "point.h"

namespace PixelMaestro {
	class Pattern {
		public:
			/// The number of rows and columns in the Pattern.
			Point *dimensions = nullptr;

			/// The number of frames in the Pattern.
			unsigned short frames;

			/// How far the Pattern is offset from the grid origin (where the origin is the first Pixel in the grid).
			Point *offset = nullptr;

			/**
				The pattern to display when the PATTERN animation is active.
				Stored as an array of bool arrays where each bool array is a separate frame.
			*/
			bool **pattern = nullptr;

			/// Whether to repeat the Pattern over the grid (requires offset to be set).
			bool repeat = false;

			/**
			 * Direction and rate for scrolling the Pattern (if applicable).
			 * Scrolling occurs on every cycle update.
			 * Setting an axis to 0 disables scrolling on that axis.
			 */
			Point *scrollRate = nullptr;

			Pattern(bool **pattern, Point *dimensions, unsigned short numFrames);
			~Pattern();
	};
}

#endif // PATTERN_H
