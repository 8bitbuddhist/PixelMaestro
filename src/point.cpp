/*
 * Point.cpp - Defines a point on a grid.
 */

#include "point.h"

namespace PixelMaestro {
	/**
	 * Constructor.
	 * @param x X-axis coordinate.
	 * @param y Y-axis coordinate.
	 */
	Point::Point(short x, short y) {
		this->x = x;
		this->y = y;
	}
}
