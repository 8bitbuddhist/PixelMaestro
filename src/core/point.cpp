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
	Point::Point(uint16_t x, uint16_t y) {
		set(x, y);
	}

	/**
	 * When used as a dimension, translates a coordinate into a 1-dimensional array index.
	 * @param point Point containing the coordinate.
	 * @return Index of the coordinate when translated to a 1D array.
	 */
	uint32_t Point::get_inline_index(Point* point) {
		return get_inline_index(point->x, point->y);
	}

	/**
	 * When used as a dimension, translates a coordinate into a 1-dimensional array index.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return Index of the coordinate when translated to a 1D array.
	 */
	uint32_t Point::get_inline_index(uint16_t x, uint16_t y) {
		return (y * this->x) + x;
	}

	/**
	 * Shortcut for setting the x and y coordinates.
	 * @param x X-axis coordinate.
	 * @param y Y-axis coordinate.
	 */
	void Point::set(uint16_t x, uint16_t y) {
		this->x = x;
		this->y = y;
	}

	/**
	 * When used as a dimension, returns x * y.
	 * @return X value multiplied by the Y value.
	 */
	uint32_t Point::size() {
		return x * y;
	}
}
