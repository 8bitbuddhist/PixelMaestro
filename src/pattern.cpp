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

	Pattern::~Pattern() {
		delete this->offset;
	}
}
