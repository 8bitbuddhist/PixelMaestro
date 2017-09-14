/*
 * Point.cpp - Defines a point on a grid.
 * Also used to define the size of a grid.
 */

#include "point.h"

namespace PixelMaestro {
	/**
	 * Constructor.
	 * @param x X-axis coordinate.
	 * @param y Y-axis coordinate.
	 */
	Point::Point(unsigned short x, unsigned short y) {
		set(x, y);
	}

	/**
	 * Shortcut for setting the x and y coordinates.
	 * @param x X-axis coordinate.
	 * @param y Y-axis coordinate.
	 */
	void Point::set(unsigned short x, unsigned short y) {
		this->x = x;
		this->y = y;
	}

	/**
	 * When used as a dimension, returns x * y.
	 * @return X value multiplied by the Y value.
	 */
	unsigned int Point::size() {
		return x * y;
	}
}
